// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	private:
		GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxBarrelDegreesPerSecond = 5;
		UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxBarrelElevationDegrees = 40;
		UPROPERTY(EditDefaultsOnly, Category = Setup) float MinBarrelElevationDegrees = 0;
	
	public: 	

		void Elevate(float RelativeSpeed);

	
};
