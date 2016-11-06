// Battle Tank

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  // -1 is max downward speed, +! is max up movement
  void Rotate(float RelativeSpeed);
  
private:

  UPROPERTY(EditAnywhere, Category = "Setup")
  float MaxDegreesPerSecond = 25.0;
	
	
};
