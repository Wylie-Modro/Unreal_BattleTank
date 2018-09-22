

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto AITank = GetAITank();
	if (!AITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Not Posessing A Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Posessing: %s"), *(AITank->GetName()));
	}

	auto PlayerTank = FindPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Not Finding Player Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Finding Player Tank: %s"), *(PlayerTank->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("Me AI Controller Begin Play"));
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (FindPlayerTank()) {

		// Move Towards the Player

		FVector PlayerTankLocation = FindPlayerTank()->GetActorLocation();

		auto AITank = GetAITank();

		AITank->AimAt(PlayerTankLocation);


		// Fire if ready

	}
	
}





ATank* ATankAIController::GetAITank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::FindPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}