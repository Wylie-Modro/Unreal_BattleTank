// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed) {
	// RelativeSpeed meaning -1 is maxDownwardSpeed, +1 is maxUpwardSpeed
	
	//Move the barrel the right amount this frame
	//Given a max elevation speed and the frame rate

	float RelativeRotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxTurretDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float RawNewRotation = RelativeRotation.Yaw + RelativeRotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Turret Rotation Called at %f"), Time, RawNewRotation);
}

