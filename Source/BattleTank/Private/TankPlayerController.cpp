// Battle Tank


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay() {
  Super::BeginPlay();

  auto AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if(!ensure(AimingComponentRef)) { return; }
    FoundAimingComponent(AimingComponentRef);
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
  Super::Tick( DeltaTime );
  AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair(){
  
  // Prevent crash if not possessing tank
  if(!GetPawn()) {
    return;
  }
  
  UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  
  if(!ensure(AimingComponent)) {
    return;
  }
  
  FVector HitLocation; //Out Parameter
  
  // Get world location linetrace through crosshair
  bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);
  
  if(bGotHitLocation) {
    // if it hits the landscape
    // Tell controlled tank to aim at this point
    AimingComponent->AimAt(HitLocation);
  }
 

}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const {
 
  // Find the crosshair position
  int32 ViewportSizeX, ViewPortSizeY;
  GetViewportSize(OUT ViewportSizeX,OUT ViewPortSizeY);

  float CrossHairXLocationInViewPort = ViewportSizeX * CrossHairXLocation;
  float CrossHairYLocationInViewPort = ViewPortSizeY * CrossHairYLocation;
  FVector2D ScreenLocation = FVector2D(CrossHairXLocationInViewPort,
                                       CrossHairYLocationInViewPort );
  
  // "De-project" the screen position of the crosshair to a world direction
  FVector LookDirection;
  if( GetLookDirection(ScreenLocation, OUT LookDirection)) {
    // line trace along that look direction, and see what we hit ( up to max range)
    return GetLookVectorHitLocation(LookDirection, OUT HitLocation);
  }
  
  return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const {
  FVector CameraWorldLocation; // To Be discarded;
  return DeprojectScreenPositionToWorld(ScreenLocation.X,
                                 ScreenLocation.Y,
                                 OUT CameraWorldLocation,
                                 OUT LookDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation ) const{

  FHitResult HitResult;
  FVector StartLocation = PlayerCameraManager->GetCameraLocation();
  FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
  
  if(GetWorld()->LineTraceSingleByChannel(HitResult,
                                          StartLocation,
                                          EndLocation,
                                          ECollisionChannel::ECC_Visibility)){
    HitLocation = HitResult.Location;
    return true;
  }
  HitLocation = FVector(0);
  return false; // Libe trace did not succeed;
}














