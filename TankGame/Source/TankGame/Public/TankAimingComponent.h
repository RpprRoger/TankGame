// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
	void PredictAndMoveTurret(FVector AimWorldLocation, float LaunchSpeed); // TODO: Find sensible default

	void SetBarrel(UTankBarrel* BarrelToSet);
	void SetTurret(UTankTurret* BarrelToSet);

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void AimCannonAt(FVector TargetPosition);
};
