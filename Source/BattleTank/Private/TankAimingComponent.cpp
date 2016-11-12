// Battle Tank

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

void UTankAimingComponent::BeginPlay() {
  
  // First Fire after initial reload
  LastFireTime = FPlatformTime::Seconds();
}



void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
  
  
  if(AmmunitionCount <= 0){
    FiringState = EFiringStatus::OutOfAmmo;
  } else if ( (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds ) {
    FiringState = EFiringStatus::Reloading;
  }else if (IsBarrelMoving()) {
    FiringState = EFiringStatus::Aiming;
  }else {
    FiringState = EFiringStatus::Locked;
  }
  
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
  Barrel = BarrelToSet;
  Turret = TurretToSet;
}


bool UTankAimingComponent::IsBarrelMoving() {
  if(!ensure(Barrel)){
    return false;
  }
  
  FVector BarrelForward = Barrel->GetForwardVector();
  
  // If barrel Equal to AimDirectiom then barrel not moving
  return !BarrelForward.Equals(AimDirection, 0.01);
}


void UTankAimingComponent::MoveBarrelTowards() {
  
  
  if(!ensure(Barrel)) {return;}
  //Work out difference between current barrel rotation, and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;
  
  if(DeltaRotator.Yaw > 180) {
    DeltaRotator.Yaw = 360 - DeltaRotator.Yaw;
  }
  
  Barrel->Elevate(DeltaRotator.Pitch); // Todo remove magic number
  
}


void UTankAimingComponent::MoveTurretTowards() {
  
  if(!ensure(Turret)) {return;}
  
  FRotator TurretRotator = Turret->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - TurretRotator;
  
  if(DeltaRotator.Yaw > 180) {
    DeltaRotator.Yaw = 360 - DeltaRotator.Yaw;
  }
  
  Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::AimAt(FVector HitLocation) {

  if(!ensure(Barrel)) {
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
    AimDirection = LaunchVElocity.GetSafeNormal();
    MoveBarrelTowards();
    MoveTurretTowards();
  }
}

void UTankAimingComponent::Fire() {
  
  if(FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming) {
    
    if(!ensure(Barrel)) {return;}
    if(!ensure(ProjectileBlueprint)) {return;}
    
    const FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
    const FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
    //Spawn projectile at socket location.
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
    AmmunitionCount = AmmunitionCount - 1;
  }
}


EFiringStatus UTankAimingComponent::GetFiringState() const {
  return FiringState;
}

int32 UTankAimingComponent::GetAmmunitionCount() const {
  return AmmunitionCount;
}





