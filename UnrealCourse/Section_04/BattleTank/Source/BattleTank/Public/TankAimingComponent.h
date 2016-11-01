// Battle Tank

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class UTankBarrel;

// Holds barrel properties. ex: Elevation.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

  
public:
  // Sets default values for this component's properties
  UTankAimingComponent();
  
  void setBarrelReference(UTankBarrel* BarrelToSet);
  
  void AimAt(FVector HitLocation, float LaunchSpeed);

  // Todo add setTurretReference
  
private:
  
  UTankBarrel* Barrel = nullptr;
	
  void MoveBarrelTowards(FVector AimDirection);
};
