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
	Locked,
	OutOfAmmo
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

	void MoveBarrelToward();
	void MoveTurretToward();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchingSpeed = 5000; // 1km/s

	UPROPERTY(EditDefaultsOnly, Category = Firing) 
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing) 
	float ReloadTime = 3;


	double LastReloadTime = 0;

	FVector AimDirection;
	
private: 
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;;
	bool BarrelIsMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing") int32 AmmoAmount = 5;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;


public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Firing) int32 GetCurrentAmmoAmount() const;

	UFUNCTION(BlueprintCallable, Category = Setup) void Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing) void Fire();

	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;
};