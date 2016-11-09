// Battle Tank

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
  
private:
  
  UPROPERTY(EditDefaultsOnly)
  float AcceptanceRadius = 30.0;
  
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaSeconds ) override;
  
 
};
