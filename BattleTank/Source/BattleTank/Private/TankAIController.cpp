

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ AI Controller Begin Play"));
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank) {

		// Move Towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at Player
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		auto AITank = Cast<ATank>(GetPawn());
		
		//UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ AimAt called in AI Controller"));
		AITank->AimAt(PlayerTankLocation);

		// Fire if ready
		//TODO: Dont Fire every frame
		AITank->Fire();
	}
	
}

