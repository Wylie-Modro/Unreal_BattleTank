// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declaration
class UTankAimingComponent;

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

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* TankAimCompRef);

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;
	
};
