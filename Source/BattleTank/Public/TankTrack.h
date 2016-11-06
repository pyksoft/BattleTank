// Battle Tank

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tracks of the tank. A Regular Tank has 2 tracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  
  UFUNCTION(BlueprintCallable, Category = "Input")
  void SetThrottle(float Throttle);
	
  // Max force per track in Newtons.
  UPROPERTY(EditDefaultsOnly)
  float TrackMaxDrivingForce = 400000; // Assume 40 tonnes tank, and 1g acceleration
  
  
};
