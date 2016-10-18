// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
  UPROPERTY(VisibleAnywhere)
  float OpenDoorAngle = -110.0f;
  UPROPERTY(VisibleAnywhere)
  float CloseDoorAngle = 180.0f;
  
  UPROPERTY(EditAnywhere)
  ATriggerVolume* PressurePlate;
  
  UPROPERTY(EditAnywhere)
  float DoorCloseDelay = 2.0f;
  
  float LastDoorOpenTime;

  
  
  AActor* OwnerPointer;
  
  void OpenDoor();
  void CloseDoor();
  float GetTotalMassOfActorsOnPlate();
  
  
};
