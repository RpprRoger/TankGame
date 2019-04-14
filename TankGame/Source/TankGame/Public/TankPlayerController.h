// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class ATank;

/**
 *
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called at the start of the game or when spawned
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333333333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	ATank* GetControlledTank() const;
	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector& OutLookDirection, FVector2D ScreenLocation) const;

	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const;
};
