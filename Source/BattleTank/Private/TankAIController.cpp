// Battle Tank

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay() {
  Super::BeginPlay();
  
  ATank* AITank = GetAITank();
  
  ATank* PlayerTank = GetPlayerTank();

}


void ATankAIController::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);
  
  ATank* PlayerTank = GetPlayerTank();
              
  if(ensure(PlayerTank)){
    // Move towards the player
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    //Aim towards the player
    GetAITank()->AimAt(PlayerTank->GetActorLocation());
    GetAITank()->Fire();
  }
  
}

ATank* ATankAIController::GetAITank() const {
  
  return Cast<ATank>(GetPawn());
  
}


ATank* ATankAIController::GetPlayerTank() const {
  
  APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if(!ensure(PlayerPawn)) {
    return nullptr;
  }
  ATank* PlayerTank = Cast<ATank>(PlayerPawn);
  return PlayerTank;
}
