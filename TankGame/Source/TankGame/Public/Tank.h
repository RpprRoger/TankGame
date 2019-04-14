// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// ForwardDeclarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AShell;

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	void AttemptAim(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

private:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = Firing)
	float FireLaunchSpeed = 40000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AShell> ProjectileBlueprint = nullptr; // Alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

	UTankBarrel* Barrel;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeInSeconds = 3.f;
	float LastFireTime = 0;
};
