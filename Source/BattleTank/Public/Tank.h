// Battle Tank

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

  
public:
  
  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelReference(UTankBarrel* BarrelToSet);
  
  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetTurretReference(UTankTurret* TurretToSet);
  
  void AimAt(FVector HitLocation);
  
  UFUNCTION(BlueprintCallable, Category = Firing)
  void Fire();
    
protected:
  UTankAimingComponent* TankAimingComponent = nullptr;
  
  UPROPERTY(BlueprintReadOnly)
  UTankMovementComponent* TankMovementComponent = nullptr;
   
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  // in cm/s
	UPROPERTY(EditDefaultsOnly, Category = Firing)
  float LaunchSpeed = 10000.0;
  
  //Reload time in s
  UPROPERTY(EditDefaultsOnly, Category = Firing)
  float ReloadTimeInSeconds = 3.0;
  
  UPROPERTY(EditDefaultsOnly, CAtegory = Setup)
  TSubclassOf<AProjectile> ProjectileBlueprint;

  // Local Barrel reference for spawing projectile
  UTankBarrel* Barrel = nullptr;

  double LastFireTime = 0.0;
  
};
