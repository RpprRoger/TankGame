// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

// -1 is max downward speed, 1 is max upward speed
void UTankTurret::Rotate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // given a max Rotation speed and the frame time
    auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * RotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

    auto Rotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, Rotation, 0));
}
