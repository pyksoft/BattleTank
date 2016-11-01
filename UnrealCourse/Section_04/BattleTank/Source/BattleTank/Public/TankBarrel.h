// Battle Tank

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
  
  // -1 is max downward speed, +! is max up movement
  void Elevate(float RelativeSpeed);
	
private:
  UPROPERTY(EditAnywhere, Category = setup)
  float MaxDegreesPerSecond = 10.0;
  
  UPROPERTY(EditAnywhere, Category = setup)
  float MaxElevationDegrees = 40.0;
  
  UPROPERTY(EditAnywhere, Category = setup)
  float MinElevationDegrees = 0.0;
};
