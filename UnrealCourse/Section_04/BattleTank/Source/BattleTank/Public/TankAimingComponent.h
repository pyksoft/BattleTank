// Battle Tank

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

  
public:
  // Sets default values for this component's properties
  UTankAimingComponent();
  
  void setBarrelReference(UStaticMeshComponent* BarrelToSet);
  
  void AimAt(FVector HitLocation);

  
  
private:
	

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

  
  UStaticMeshComponent* Barrel = nullptr;
	
};
