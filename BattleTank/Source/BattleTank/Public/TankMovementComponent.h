// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

public: 

	UFUNCTION(BlueprintCallable, Category = Setup) void Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveBackward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveRight(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveLeft(float Throw);
	
	// Called from the pathfinding logic in AI controller
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
