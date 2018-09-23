// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declaration
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	void AimThroughCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector WorldLookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly) float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly) float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly) float LineTraceRange = 1000000;

public:
	ATank* GetControlledTank() const;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;
	
};
