// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrel(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::PredictAndMoveTurret(FVector AimWorldLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	FVector LaunchVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		AimWorldLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameters must be present to reliably get aiming solution
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), GetWorld()->GetTimeSeconds());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%f NO***** aim solution found"), GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector TargetPosition)
{
	if (!Barrel) { return; }
	// Current Barrel rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	// Calculate Roll, Pitch, and Yaw to make barrel match TargetPosition
	auto DeltaRotator = TargetPosition.Rotation() - BarrelRotation;

	// Apply result to barrel mesh
	Barrel->Elevate(5); // TODO remove magic number
}
