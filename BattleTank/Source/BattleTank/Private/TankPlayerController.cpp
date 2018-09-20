// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimThroughCrosshair();
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayController Not Posessing A Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayController Posessing: %s"), *(ControlledTank->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("Me Player Controller Begin Play"));
}

ATank* ATankPlayerController::GetControlledTank() const {
	
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimThroughCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {

	//Find CrossHair Position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * ATankPlayerController::CrosshairXLocation, ViewportSizeY * ATankPlayerController::CrosshairYLocation);

	return true;
}

