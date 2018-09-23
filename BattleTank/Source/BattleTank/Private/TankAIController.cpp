

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Me AI Controller Begin Play"));
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank) {

		// Move Towards the Player

		// Aim at Player
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		auto AITank = Cast<ATank>(GetPawn());
		AITank->AimAt(PlayerTankLocation);

		// Fire if ready
		//TODO: Dont Fire every frame
		AITank->Fire();
	}
	
}

