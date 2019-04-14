// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto ControlledTank = Cast<ATank>(GetPawn());
    auto PlayerTankController = GetWorld()->GetFirstPlayerController();

    if (!PlayerTankController || !ControlledTank) { return; }

    auto PlayerTank = Cast<ATank>(PlayerTankController->GetPawn());
    if (PlayerTank) {

        // TODO: Move towards the player

        // Start aiming towards the player
        ControlledTank->AttemptAim(PlayerTank->GetActorLocation());

        // FIREEEEEEEE
        ControlledTank->Fire(); // TODO Make the AI tank more human in its firing
    }
}
