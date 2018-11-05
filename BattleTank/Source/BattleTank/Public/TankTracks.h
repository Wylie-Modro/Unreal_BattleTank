// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input) void SetThrottle(float Throttle);

	TArray<class ASprungWheel*> GetWheels() const;

private:
	UPROPERTY(EditDefaultsOnly) float MaxTrackDrivingForce = 100000; //100kN 
	UTankTracks();
	virtual void BeginPlay() override;

	void DriveTrack(float CurrentTrack);
};