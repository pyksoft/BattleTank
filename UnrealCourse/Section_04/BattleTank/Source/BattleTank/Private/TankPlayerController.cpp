// Battle Tank

#include "BattleTank.h"
#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay() {
  Super::BeginPlay();
  
  ATank* ControlledTank = GetControlledTank();
  
  if(!ControlledTank) {
    UE_LOG(LogTemp, Warning, TEXT("Not possesing a tank"));
  }
  
  UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin %s"), *(ControlledTank->GetName()));

}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
  Super::Tick( DeltaTime );


  //AimTowardsCrosshair
  
  
}


ATank* ATankPlayerController::GetControlledTank() const {
  
 return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardCrosshair(){
  if(!GetControlledTank()){
    return;
  }
  
}
