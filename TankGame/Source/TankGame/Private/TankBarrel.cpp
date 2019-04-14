// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

// -1 is max downward speed, 1 is max upward speed
void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // given a max elevation speed and the frame time
    auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * ElevationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinBarrelElevation, MaxBarrelElevation);

    SetRelativeRotation(FRotator(Elevation, 0, 0));
}
