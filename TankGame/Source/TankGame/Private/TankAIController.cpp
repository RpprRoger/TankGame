// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *ControlledTank->GetName());
        auto PlayerTank = GetPlayerControlledTank();

        if (!PlayerTank) {
            UE_LOG(LogTemp, Warning, TEXT("AIController:%s doesn't find a player"), *ControlledTank->GetName());
        } else {
            UE_LOG(LogTemp, Warning, TEXT("AIController:%s found player %s"), *ControlledTank->GetName(), *PlayerTank->GetName());
        }
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!GetControlledTank() || !GetPlayerControlledTank()) { return; }
    // TODO: Move towards the player

    // Start aiming towards the player
    GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

    // FIREEEEEEEE
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
    auto PlayerTankController = GetWorld()->GetFirstPlayerController();

    if (!PlayerTankController) {
        return nullptr;
    }

    return Cast<ATank>(PlayerTankController->GetPawn());
}