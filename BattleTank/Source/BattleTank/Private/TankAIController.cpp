

#include "TankAIController.h"
//#include "Tank.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ AI Controller Begin Play"));
}


void ATankAIController::Tick(float DeltaTime) {
	UE_LOG(LogTemp, Warning, TEXT("AI Controller Before Super"));
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("AI Controller After Super"));
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Before check"));
	if (!ensure(PlayerTank && AITank)) { return; }

		UE_LOG(LogTemp, Warning, TEXT("AI Controller I Get here"));

		// Move Towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at Player
		FVector PlayerTankLocation = PlayerTank->GetActorLocation();
		
		//UE_LOG(LogTemp, Warning, TEXT("BlackIce: C++ AimAt called in AI Controller"));
		//AITank->AimAt(PlayerTankLocation);
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return;	}
		AimingComponent->AimAt(PlayerTankLocation);

		// Fire if ready
		//TODO: Dont Fire every frame
		//AITank->Fire();
	
}

