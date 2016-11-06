// Battle Tank


#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay() {
  Super::BeginPlay();

  auto AimingComponentRef = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
  if(!ensure(AimingComponentRef)) { return; }
    FoundAimingComponent(AimingComponentRef);
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
  Super::Tick( DeltaTime );
  AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
 return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair(){
  if(!ensure(GetControlledTank())) {
    return;
  }
  
  FVector HitLocation; //Out Parameter
  
   // Get world location linetrace through crosshair
  if(GetSightRayHitLocation(OUT HitLocation)) {
    // if it hits the landscape
    // Tell controlled tank to aim at this point
    GetControlledTank()->AimAt(HitLocation);
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
    GetLookVectorHitLocation(LookDirection, OUT HitLocation);
  }
  
  return true;
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














