

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!ensure(PlayerTank && AITank)) { return; }

		// Move Towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at Player
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return;	}
		AimingComponent->AimAt(PlayerTankLocation);

		// Fire if ready
		//TODO: Dont Fire every frame
		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
}

