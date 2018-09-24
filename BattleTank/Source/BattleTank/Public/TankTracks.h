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
	
private:
	UPROPERTY(EditDefaultsOnly) float MaxTrackDrivingForce = 400000; //400kN = 10m/s^2* 40,000kg
};
