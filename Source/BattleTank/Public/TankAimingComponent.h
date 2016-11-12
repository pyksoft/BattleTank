// Battle Tank

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringStatus : uint8 {
  Locked,
  Aiming,
  Reloading,
  OutOfAmmo
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
  
  EFiringStatus GetFiringState() const;
  
  UFUNCTION(BlueprintCallable, Category = "Firing")
  int32 GetAmmunitionCount() const ;
  
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
  
  FVector AimDirection;
  
  double LastFireTime = 0.0;
  
  bool IsBarrelMoving();
  
  void MoveBarrelTowards();
  void MoveTurretTowards();

  // in cm/s
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 5000.0;
	 
  //Reload time in s
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3.0;
  
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  int32 AmmunitionCount = 10;
  
  UPROPERTY(EditDefaultsOnly, CAtegory = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;
  

};
