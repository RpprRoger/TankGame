// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
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
    OutHitLocation = FVector(1.f, 2.f, 3.f);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
    GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

    auto EndLine = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 60000.f;

    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation,
        EndLine,
        FColor(255, 0, 0),
        false,
        0,
        0,
        10.f
    );

    return false;
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
