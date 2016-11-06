// Battle Tank


#include "BattleTank.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
  
}

void ATank::BeginPlay(){
  Super::BeginPlay(); // Needed in Blueprint !
  
  TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
};


void ATank::AimAt(FVector HitLocation) {
  if(!ensure(TankAimingComponent)) { return;}
  
  TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
  
  bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  
  if(!ensure(Barrel)) {return;}
  
  
  if(isReloaded) {
        
    const FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
    const FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
    //Spawn projectile at socket location.
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}


