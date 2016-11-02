// Battle Tank

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
  UFUNCTION(BlueprintCallable, Category = Movement)
  void IntendMoveForward(float Throw);
	
};
