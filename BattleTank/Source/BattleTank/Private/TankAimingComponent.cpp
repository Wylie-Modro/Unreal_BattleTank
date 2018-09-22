// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO: Does this really need to tick

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	
	if (!Barrel) { return; }

	FVector OutLaunchVelocity; 
	FVector StartingLocation = Barrel->GetSocketLocation(FName("Projectile"));


	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartingLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		// Default values must be present above to prevent bug
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto TankName = GetOwner()->GetName();

		MoveBarrelToward(AimDirection);

		auto OurTankName = GetOwner()->GetName();
		//auto BarrelLocation = Barrel->GetComponentLocation();

		//UE_LOG(LogTemp, Warning, TEXT("%s Aims at %s from barrel %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), LaunchSpeed);
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: %s aiming at %s"), Time, *OurTankName, *AimDirection.ToString());
	}
	else {
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Can't Find Suggested Projectile Velocity"), Time);
	}
	
	
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection) {

	//Work out difference between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotation = AimDirection.Rotation();
	auto DeltaRotation = AimDirectionRotation - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("Aim Rotation: %s, Barrel Rotation: %s"), *AimDirectionRotation.ToString(), *BarrelRotation.ToString());

	Barrel->Elevate(DeltaRotation.Pitch);

	//	Adjust barrel azamuth to match the opposite side of the triangels length whhich should be the AimDirection.Z - the default Z of the barrel off the ground 
	// Adjust the turrel angel to give the adjasent side of base trangel the same as the unit vector of AimDirection.x and y
}