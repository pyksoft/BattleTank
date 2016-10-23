// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorEvent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
  
  
  UPROPERTY(BluePrintAssignable)
  FDoorEvent OnOpenRequest;
  
  UPROPERTY(BluePrintAssignable)
  FDoorEvent OnCloseRequest;
  
  UPROPERTY(EditAnywhere)
  ATriggerVolume* PressurePlate = nullptr;

private:

  
  AActor* OwnerPointer;
  
  UPROPERTY(EditAnywhere)
  float TriggerMass = 30.f;
  
  void OpenDoor();
  void CloseDoor();
  float GetTotalMassOfActorsOnPlate();
  
  
};
