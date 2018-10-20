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
	PrimaryComponentTick.bCanEverTick = true; // TODO: Does this really need to tick
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	// So first fire is after inital reload
	LastReloadTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::Initialise(UTankBarrel* TankBarrelToSet, UTankTurret* TankTurretToSet) {
	if (!ensure(TankBarrelToSet && TankTurretToSet)) { return; }
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

void UTankAimingComponent::TickComponent(float sDeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) { 
	if (AmmoAmount <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastReloadTime) < ReloadTime) {
		FiringState = EFiringState::Reloading;
	}
	else if (BarrelIsMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity; 
	FVector StartingLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartingLocation, HitLocation, LaunchingSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		// Default values must be present above to prevent bug
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelToward();
		MoveTurretToward();

		auto OurTankName = GetOwner()->GetName();
		float Time = GetWorld()->GetTimeSeconds();
	}
	else {
		float Time = GetWorld()->GetTimeSeconds();
	}
	
	
}

void UTankAimingComponent::MoveBarrelToward() {
	if (!ensure(Barrel)) { return; }
	
	//Work out difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotation = AimDirection.Rotation();
	auto DeltaRotation = AimDirectionRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
}


void UTankAimingComponent::MoveTurretToward() {
	if (!ensure(Turret)) { return; }

	//Work out difference between current barrel rotation and AimDirection
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimDirectionRotation = AimDirection.Rotation();
	auto DeltaRotation = AimDirectionRotation - TurretRotation;

	if (FMath::Abs(DeltaRotation.Yaw) < 180) {
		Turret->RotateTurret(DeltaRotation.Yaw);
	}
	else {
		Turret->RotateTurret(-DeltaRotation.Yaw);
	}
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) { return; }

	auto entityName = GetOwner()->GetName();
	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchingSpeed);

		AmmoAmount--;
		LastReloadTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::BarrelIsMoving() {
	if (!ensure(Barrel)) { return false; }
	auto AimNForwardEql = Barrel->GetForwardVector().Equals(AimDirection , 0.01f);
	return !AimNForwardEql;
}

int32 UTankAimingComponent::GetCurrentAmmoAmount() const {
	return AmmoAmount;
}
