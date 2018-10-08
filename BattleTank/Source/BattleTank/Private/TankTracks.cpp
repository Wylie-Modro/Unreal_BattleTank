// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks::UTankTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplyCorrectiveSidewaysForce();
	CurrentThrottle = 0;
}

void UTankTracks::ApplyCorrectiveSidewaysForce() {
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAccel = (-SlippageSpeed / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccel)/2; //Two Tracks
	TankRoot->AddForce(CorrectionForce);
	//UE_LOG(LogTemp, Warning, TEXT("ICON!!! Slippage Speed: %f"), SlippageSpeed);
}

void UTankTracks::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTracks::DriveTrack() {
	float Time = GetWorld()->GetTimeSeconds(); auto Name = GetName();

	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
