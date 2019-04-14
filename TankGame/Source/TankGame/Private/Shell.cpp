// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AShell::AShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShellMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	ShellMovement->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AShell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShell::Launch(float Speed)
{
    UE_LOG(LogTemp, Warning, TEXT("Launch this"));

	ShellMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ShellMovement->Activate();
}
