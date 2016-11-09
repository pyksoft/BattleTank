// Battle Tank

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

#define OUT

class UTankAimingComponent;


/**
 * The player Controller.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
  
  //Doesnt need implementation with macro.
  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
  void FoundAimingComponent(UTankAimingComponent* AimCompRef);
  
private:
  
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaSeconds ) override;
	

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
