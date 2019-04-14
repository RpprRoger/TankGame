// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *GetName(), Throttle);

    if (Throttle && Throttle != 0.f)
    {
        auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1, 1);
        auto ForceApplied = GetForwardVector() * ClampedThrottle * MaxDrivingForce;
        auto ForceLocation = GetComponentLocation();
        auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    }
}
