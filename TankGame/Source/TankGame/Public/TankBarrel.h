// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Tank Barrel with barrel configuration and elevation controls
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=("Physics") )
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    // Move the barrel the right amount this frame
    // given a max elevation speed and the frame time
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Aiming)
	float ElevationDegreesPerSecond = 5.f; // Guess at a sensible default

	UPROPERTY(EditAnywhere, Category = Aiming)
	float MaxBarrelElevation = 40.f; // Guess at a sensible default

	UPROPERTY(EditAnywhere, Category = Aiming)
	float MinBarrelElevation = 0.f; // Guess at a sensible default
};
