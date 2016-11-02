// Battle Tank


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
  
  TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
  TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
  
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void ATank::Fire() {
  
  bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  
  
  
  if(Barrel && isReloaded) {
    
    UE_LOG(LogTemp,Warning, TEXT("%d: FIRING at %d"), FPlatformTime::Seconds(), LastFireTime);
    
    const FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
    const FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
    //Spawn projectile at socket location.
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}



void ATank::AimAt(FVector HitLocation) {
  TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
  TankAimingComponent->SetBarrelReference(BarrelToSet);
  Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
  TankAimingComponent->SetTurretReference(TurretToSet);
}


