// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Set the throttle of this tank track, between -1 and 1
	// TODO Clamp actual throttle so user can't overdrive
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// The max force to apply to this track, in newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 4000000.f; // Assume tank of 40 tonne and 1g of acceleration
};
