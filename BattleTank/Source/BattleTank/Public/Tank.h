// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankAimingComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup) void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup) void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing) void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing) float LaunchingSpeed = 100000; // 1km/s

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing) TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// Local barrel declared here for projectile spawning 
	UTankBarrel* Barrel = nullptr;

	float ReloadTime = 3;

	double LastReloadTime = 0;

};
