// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP to run!
	CurrentHealth = InitialHealth; // intialized here so can take value from BP
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {

	int32 DamageFloatToInt = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamageFloatToInt, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {

		OnDeath.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("Tank got recked"));
	}

	UE_LOG(LogTemp, Warning, TEXT("DamageToApply: %i"), DamageToApply) 
	return DamageToApply;
}

float ATank::GetCurrentHealthPercent() const {
	auto CurrentHealthPercent = (float)CurrentHealth / (float)InitialHealth;

	//UE_LOG(LogTemp, Warning, TEXT("CurrentHealth %f"), CurrentHealth);
//	UE_LOG(LogTemp, Warning, TEXT("InitialHealth: %f"), InitialHealth);
//	UE_LOG(LogTemp, Warning, TEXT("CurrentHealthPercent: %f"), CurrentHealthPercent);

	return CurrentHealthPercent;
}
