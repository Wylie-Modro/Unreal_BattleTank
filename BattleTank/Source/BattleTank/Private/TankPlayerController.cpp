// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ Player Controller BeginPlay"));

	ATank* ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank)) { return;  }

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	} else{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller cannot find TankAimingComponent in BeginPlay"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimThroughCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimThroughCrosshair() {
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
	//	UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ AimAt called Player Controller"));
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {

	//Find CrossHair Position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * ATankPlayerController::CrosshairXLocation, ViewportSizeY * ATankPlayerController::CrosshairYLocation);

	FVector	WorldLookDirection;
	FVector	WorldCameraLocation;

	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldCameraLocation, WorldLookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("WorldLookDirection: %s"), *WorldLookDirection.ToString());
	GetLookVectorHitLocation(WorldLookDirection, OutHitLocation);
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldLookDirection, FVector& OutHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
		//UE_LOG(LogTemp, Warning, TEXT("StartLocation: %s"), *StartLocation.ToString());
	auto EndLocation = StartLocation + (WorldLookDirection * LineTraceRange);
		//UE_LOG(LogTemp, Warning, TEXT("EndLocation: %s"), *EndLocation.ToString());


	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0);
	return false;
}

