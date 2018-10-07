// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "kismet/GamePlayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};


//Forward Declaration
class UTankBarrel;
class AProjectile;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelToward(FVector AimDirection);
	void MoveTurretToward(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchingSpeed = 5000; // 1km/s

	UPROPERTY(EditDefaultsOnly, Category = Firing) 
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTime = 3;
	double LastReloadTime = 0;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup) void Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing) void Fire();

	void AimAt(FVector HitLocation);
};