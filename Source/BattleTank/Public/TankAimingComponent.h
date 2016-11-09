// Battle Tank

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringStatus : uint8 {
  Locked,
  Aiming,
  Reloading
};


// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel properties. ex: Elevation.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

  
public:

  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
  
  void AimAt(FVector HitLocation);

  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();
  
  
  
protected:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringStatus FiringState = EFiringStatus::Reloading;

  
private:
  
  // Sets default values for this component's properties
  UTankAimingComponent();
  
  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
  virtual void BeginPlay() override;
  
  UTankBarrel* Barrel = nullptr;
  UTankTurret* Turret = nullptr;
  
  // in cm/s
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 10000.0;
	 
  //Reload time in s
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0;
  
  UPROPERTY(EditDefaultsOnly, CAtegory = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;
  
  double LastFireTime = 0.0;
  
  
  void MoveBarrelTowards(FVector AimDirection);
  void MoveTurretTowards(FVector AimDirection);
  

};
