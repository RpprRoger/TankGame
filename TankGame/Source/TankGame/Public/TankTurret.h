// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=("Physics", "Collision") )
class TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Aiming)
	float RotationDegreesPerSecond = 18.f; // Near the real t-62 from wikipedia

public:
	void Rotate(float RelativeSpeed);
};
