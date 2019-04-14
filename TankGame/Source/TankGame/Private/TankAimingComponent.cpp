// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector AimWorldLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));

	FVector LaunchVelocity;
	bool bCanLaunch = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		AimWorldLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bCanLaunch)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("aiming at: %s from"),
			*AimDirection.ToString()
		);
	}
}
