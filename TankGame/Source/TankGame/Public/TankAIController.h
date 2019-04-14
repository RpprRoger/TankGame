// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// ForwardDeclarations
class ATank;

/**
 *
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called at the start of the game or when spawned
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerControlledTank() const;
};
