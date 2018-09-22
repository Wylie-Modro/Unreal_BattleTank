// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public: 	

		void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup) float MaxDegreesPerSecond = 5;
	UPROPERTY(EditAnywhere, Category = Setup) float MaxBarrelElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = Setup) float MinBarrelElevationDegrees = 0;
	
};
