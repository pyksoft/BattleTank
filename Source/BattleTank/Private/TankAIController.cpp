// Battle Tank

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay() {
  Super::BeginPlay();
  
}


void ATankAIController::Tick(float DeltaSeconds) {
  
  Super::Tick(DeltaSeconds);
  
  APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
  APawn* ControlledTank = GetPawn();
  
  if(!ensure(PlayerTank && ControlledTank)){
    return;
  }
  
  // Move towards the player
  MoveToActor(PlayerTank, AcceptanceRadius);
    
  //Aim towards the player
  UTankAimingComponent* AimingComponent =
  ControlledTank->FindComponentByClass<UTankAimingComponent>();
  
  AimingComponent->AimAt(PlayerTank->GetActorLocation());
  
  AimingComponent->Fire();
  
}
