// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//Prevent double spped dude ot due control use
}

void UTankMovementComponent::IntendMoveBackward(float Throw) {

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);
	//Prevent double spped dude ot due control use
}

void UTankMovementComponent::IntendMoveRight(float Throw) {

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//Prevent double spped dude ot due control use
}

void UTankMovementComponent::IntendMoveLeft(float Throw) {

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	//Prevent double spped dude ot due control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	
	auto CurrentAITankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto IntendedAITankForwardVector = MoveVelocity.GetSafeNormal();

	auto RelativeThrowGivenVectors = FVector::DotProduct(CurrentAITankForwardVector, IntendedAITankForwardVector);
	// RelativeThrowGiven the difference of the currentVector of Tank and the desired Vector

	if (RelativeThrowGivenVectors >= 0) {
		IntendMoveForward(RelativeThrowGivenVectors);
	}
	else {
		IntendMoveBackward(-RelativeThrowGivenVectors);
	}

	float RelativeRotationGivenVectors = FVector::CrossProduct(CurrentAITankForwardVector, IntendedAITankForwardVector).Z;

	if (RelativeRotationGivenVectors >= 0) {
		IntendMoveRight(RelativeRotationGivenVectors);
	}
	else {
		IntendMoveLeft(-RelativeRotationGivenVectors);
	}
}

