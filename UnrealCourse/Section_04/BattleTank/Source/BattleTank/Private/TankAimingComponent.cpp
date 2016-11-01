// Battle Tank

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

  if(!Barrel) {
    return;
  }
  
  FVector OUT LaunchVElocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  
  // Calculate the Out Lanch Velocity

  bool bHaveAimSolution =
    UGameplayStatics::SuggestProjectileVelocity(this,
                                                OUT LaunchVElocity,
                                                StartLocation,
                                                HitLocation,
                                                LaunchSpeed,
                                                false,
                                                0,
                                                0,
                                                ESuggestProjVelocityTraceOption::DoNotTrace); //Parameter must be present.
  
  if(bHaveAimSolution){
    FVector AimDirection = LaunchVElocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
  }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
  
  //Work out difference between current barrel rotation, and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(DeltaRotator.Pitch); // Todo remove magic number
  
}


void UTankAimingComponent::setBarrelReference(UTankBarrel* BarrelToSet){
  Barrel = BarrelToSet;
}
