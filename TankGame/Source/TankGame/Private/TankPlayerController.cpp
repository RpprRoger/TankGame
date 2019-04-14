// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank"));
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        GetControlledTank()->AttemptAim(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    // the crosshair position relative to the viewport size
    auto CrosshairPosition = FVector2D(
        ViewportSizeX * CrossHairXLocation,
        ViewportSizeY * CrossHairYLocation
    );

    /// TODO: GetHitResultAtScreenPosition exists, it's far cleaner
	FVector LookDirection;
    if (GetLookDirection(LookDirection, CrosshairPosition))
    {
        return GetLookVectorHitLocation(OutHitLocation, LookDirection);
    }

    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
    FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
    FVector LineTraceEnd = LineTraceStart + LookDirection * LineTraceRange;

    /// Line-trace along that look direction, and see what we hit (up to a max range);
    FHitResult HitResult;
    const bool HitSomethingVisible = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        LineTraceStart,
        LineTraceEnd,
        ECollisionChannel::ECC_Visibility,
        FCollisionQueryParams()
    );

    if (HitSomethingVisible)
    {
        OutHitLocation = HitResult.Location;
    }

    return HitSomethingVisible;
}

// De-project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector& OutLookDirection, FVector2D ScreenLocation) const
{
    // Drop this value
	FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        OutLookDirection
    );
}
