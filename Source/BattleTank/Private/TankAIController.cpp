// Battle Tank

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
  Super::BeginPlay();
  
  ATank* AITank = GetAITank();
  
  ATank* PlayerTank = GetPlayerTank();
  
  if(!AITank) {
    UE_LOG(LogTemp, Warning, TEXT("Not possesing a tank"));
  }
  
  if(!PlayerTank) {
    UE_LOG(LogTemp, Warning, TEXT("Could not find the player tank"));

  }
  
  UE_LOG(LogTemp, Warning, TEXT("AIController Begin %s"), *(AITank->GetName()));
  UE_LOG(LogTemp, Warning, TEXT("PlayerTank Found %s"), *(PlayerTank->GetName()));
  
}


void ATankAIController::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);
  
  if(GetPlayerTank()){
    // TODO Move towards the player
    
    
    //Aim towards the player
    GetAITank()->AimAt(GetPlayerTank()->GetActorLocation());
  }
  
}

ATank* ATankAIController::GetAITank() const {
  
  return Cast<ATank>(GetPawn());
  
}


ATank* ATankAIController::GetPlayerTank() const {
  
  APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if(!PlayerPawn) {
    return nullptr;
  }
  ATank* PlayerTank = Cast<ATank>(PlayerPawn);
  return PlayerTank;
}
