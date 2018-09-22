// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	// RelativeSpeed meaning -1 is maxDownwardSpeed, +1 is maxUpwardSpeed
	
	//Move the barrel the right amount this frame
	//Given a max elevation speed and the frame rate

	float RelativeElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float RawNewElevation = RelativeRotation.Pitch + RelativeElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinBarrelElevationDegrees, MaxBarrelElevationDegrees), 0, 0));

	float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Elevate Called at %f"), Time, RelativeSpeed);
}



