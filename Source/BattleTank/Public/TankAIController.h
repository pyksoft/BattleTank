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
 
  
protected:
  
  UPROPERTY(EditAnywhere, Category = "Setup")
  float AcceptanceRadius = 8000; //in cm
  
private:
  
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaSeconds ) override;
  
 
};
