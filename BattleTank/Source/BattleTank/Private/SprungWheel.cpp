// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(PhysicsConstraint);

	TankWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankWheel"));
	TankWheel->SetupAttachment(RootComponent);

	
	//auto ParentActor = execGetAttachParentActor();
	//UE_LOG(LogTemp, Warning, "ParentActor: %s", ParentActor);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	auto TankActor = GetAttachParentActor();
	if (TankActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got AttachParentActor"));

		PhysicsConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(TankActor->GetRootComponent()), NAME_None, TankWheel, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

