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

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    // the crosshair position relative to the viewport size
    auto CrosshairPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairXLocation);

	FVector LookDirection;
    const bool Ok = GetLookDirection(CrosshairPosition, LookDirection);


    // Line-trace along that look direction, and see what we hit (up to a max range);

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    /// De-project the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    auto HitLandscape = GetSightRayHitLocation(HitLocation);

    if (HitLandscape)
    {
        // UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s, success: %s"), *HitLocation.ToString(), *FString(Success ? "true" : "false"));
    }
}
