// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * TankTurret is used to add a turret which has rotation controls
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float RotationDegreesPerSecond = 18.f; // Near the real t-62 from wikipedia
};
