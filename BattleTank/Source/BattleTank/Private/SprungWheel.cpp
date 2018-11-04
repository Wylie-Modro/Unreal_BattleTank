// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankToAxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("TankToAxelConstraint"));
	SetRootComponent(TankToAxelConstraint);

	TankAxel= CreateDefaultSubobject<USphereComponent>(FName("TankAxel"));
	TankAxel->SetupAttachment(RootComponent);

	AxelToWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxelToWheelConstraint"));
	AxelToWheelConstraint->SetupAttachment(TankAxel);

	TankWheel= CreateDefaultSubobject<USphereComponent>(FName("TankWheel"));
	TankWheel->SetupAttachment(TankAxel);
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

		TankToAxelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(TankActor->GetRootComponent()), NAME_None, TankAxel, NAME_None);
		AxelToWheelConstraint->SetConstrainedComponents(TankAxel, NAME_None, TankWheel, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
