// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

// De-project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    // Drop this value
	FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult Hit;
    FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();

    // Line-trace along that look direction, and see what we hit (up to a max range);
    return GetWorld()->LineTraceSingleByChannel(
        Hit,
        LineTraceStart,
        LineTraceStart + LookDirection * LineTraceRange,
        ECC_Visibility
    );
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    // the crosshair position relative to the viewport size
    auto CrosshairPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairXLocation);

	FVector LookDirection;
    if (GetLookDirection(CrosshairPosition, LookDirection)) {
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }

    return false;
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        DrawDebugLine(
            GetWorld(),
            PlayerCameraManager->GetCameraLocation(),
            HitLocation,
            FColor(255, 0, 0),
            true,
            1,
            0,
            10.f
        );
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
    }
}
