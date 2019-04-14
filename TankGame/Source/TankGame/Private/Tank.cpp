// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Shell.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	if (!ProjectileBlueprint) {
		UE_LOG(LogTemp, Error, TEXT("Tank %s is missing ProjectileBlueprint"), *GetName());
	}
}

void ATank::SetBarrel(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrel(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurret(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurret(TurretToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AttemptAim(FVector Location)
{
	TankAimingComponent->PredictAndMoveTurret(Location, FireLaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel || !ProjectileBlueprint) { return; }

	AShell* Projectile = GetWorld()->SpawnActor<AShell>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Muzzle")),
		Barrel->GetSocketRotation(FName("Muzzle"))
	);

	Projectile->Launch(FireLaunchSpeed);
}
