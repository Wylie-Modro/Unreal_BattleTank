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
