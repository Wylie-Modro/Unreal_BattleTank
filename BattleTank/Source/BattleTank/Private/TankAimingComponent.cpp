// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // TODO: Does this really need to tick
}

void UTankAimingComponent::Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet) {
	if (!ensure(TankBarrelToSet && TankTurretToSet)) { return; }
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity; 
	FVector StartingLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartingLocation, HitLocation, LaunchingSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		// Default values must be present above to prevent bug
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelToward(AimDirection);
		MoveTurretToward(AimDirection);

		auto OurTankName = GetOwner()->GetName();
		float Time = GetWorld()->GetTimeSeconds();
	}
	else {
		float Time = GetWorld()->GetTimeSeconds();
	}
	
	
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {
	if (!ensure(Barrel)) { return; }
	
	//Work out difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotation = AimDirection.Rotation();
	auto DeltaRotation = AimDirectionRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
}


void UTankAimingComponent::MoveTurretToward(FVector AimDirection) {
	if (!ensure(Turret)) { return; }

	//Work out difference between current barrel rotation and AimDirection
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimDirectionRotation = AimDirection.Rotation();
	auto DeltaRotation = AimDirectionRotation - TurretRotation;

	Turret->RotateTurret(DeltaRotation.Yaw);
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastReloadTime) > ReloadTime;
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchingSpeed);
		LastReloadTime = FPlatformTime::Seconds();
	}
}

