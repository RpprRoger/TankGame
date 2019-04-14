// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Tank Barrel with barrel configuration and elevation controls
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    // Move the barrel the right amount this frame
    // given a max elevation speed and the frame time
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float ElevationDegreesPerSecond = 5.f; // Guess at a sensible default

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float MaxBarrelElevation = 20.f; // Near the real t-62 from wikipedia

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float MinBarrelElevation = -1.f; // Near the real t-62 from wikipedia
};
