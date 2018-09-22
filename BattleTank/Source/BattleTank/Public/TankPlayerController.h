// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	void AimThroughCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector WorldLookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere) float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere) float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere) float LineTraceRange = 1000000;

public:
	ATank* GetControlledTank() const;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;
	
};
