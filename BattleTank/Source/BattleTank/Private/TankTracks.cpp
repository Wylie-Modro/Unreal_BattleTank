// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle) {

	float Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttling at %f"), Time, *Name, Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



