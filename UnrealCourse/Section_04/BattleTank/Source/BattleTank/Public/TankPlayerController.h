// Battle Tank

#pragma once


#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
  ATank* GetControlledTank() const;
  
  
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaSeconds ) override;
	
  void AimTowardCrosshair();
  
};
