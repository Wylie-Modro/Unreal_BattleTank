// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{

private:
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxTurretDegreesPerSecond = 20;
	
	
public:
	void RotateTurret(float RelativeSpeed);
	
	
};
