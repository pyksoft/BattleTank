// Battle Tank

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

  
public:
  
  virtual void BeginPlay() override;
  
  
  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();
  
  void AimAt(FVector HitLocation);
  
protected:
  UPROPERTY(BlueprintReadOnly)
  UTankAimingComponent* TankAimingComponent = nullptr;

   
private:
	// Sets default values for this pawn's properties
	ATank();
  
	
	// in cm/s
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 10000.0;
  
  //Reload time in s
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0;
  
  UPROPERTY(EditDefaultsOnly, CAtegory = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  double LastFireTime = 0.0;
  
  UTankBarrel* Barrel = nullptr;
  
};
