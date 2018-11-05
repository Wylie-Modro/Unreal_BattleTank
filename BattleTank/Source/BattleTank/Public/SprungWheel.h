// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Component") USphereComponent* TankWheel= nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") USphereComponent* TankAxel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") UPhysicsConstraintComponent* TankToAxelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") UPhysicsConstraintComponent* AxelToWheelConstraint = nullptr;

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceMagnitude);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
