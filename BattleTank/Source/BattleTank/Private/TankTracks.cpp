// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTracks::UTankTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::BeginPlay() {
	Super::BeginPlay();
}

void UTankTracks::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

TArray<class ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;

	TArray<USceneComponent*> Childern;
		
	GetChildrenComponents(true, Childern);

	for (USceneComponent* Child : Childern)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }

		Wheels.Add(SprungWheel);
	}

	return Wheels;
}


void UTankTracks::DriveTrack(float CurrentThrottle) {
	float Time = GetWorld()->GetTimeSeconds(); auto Name = GetName();

	auto ForceMagApplied = CurrentThrottle * MaxTrackDrivingForce;
	auto Wheels = GetWheels();
	auto ForceMagPerWheel = ForceMagApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForceMagPerWheel);
	}
}
