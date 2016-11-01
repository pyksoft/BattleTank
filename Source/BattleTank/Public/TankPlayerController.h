// Battle Tank

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

#define OUT

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
  
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaSeconds ) override;
	
  
  ATank* GetControlledTank() const;
  void AimTowardsCrosshair();
  bool GetSightRayHitLocation( OUT FVector& HitLocation ) const;
  bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;
  bool GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const;
  
  UPROPERTY(VisibleAnywhere)
  float LineTraceRange = 1000000.0; // 10km
  
  UPROPERTY(EditAnywhere)
  float CrossHairXLocation = 0.5;
  
  UPROPERTY(EditAnywhere)
  float CrossHairYLocation = 0.33333;
  
  
  
};
