// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorEvent.h"

#define OUT

// Sets default values for this component's properties
UDoorEvent::UDoorEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
  
  OwnerPointer = GetOwner();
}




// Called when the game starts
void UDoorEvent::BeginPlay()
{
	Super::BeginPlay();

	// ...
  
  
}


// Called every frame
void UDoorEvent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
  
  // Poll the triigger volume every frame
  // TODO dont hardcode weight.
  if(GetTotalMassOfActorsOnPlate() > TriggerMass)  {
    UE_LOG(LogTemp, Warning, TEXT("opening door") );
    OnOpenRequest.Broadcast();
    
  }else {
    //CloseDoor();
    OnCloseRequest.Broadcast();
  }
  
 
  
}

void UDoorEvent::OpenDoor() {
  // Find the owning actor
  
 
}

void UDoorEvent::CloseDoor() {
  // Find the owning actor
  
  OnCloseRequest.Broadcast();
}


float UDoorEvent::GetTotalMassOfActorsOnPlate() {
  if(!PressurePlate) {
    return 0.0f;
  }
  
  
  float TotalMass = 0.f;
  float ActorsMass = 0;
  
  // Find all overlapping actors
  TArray<AActor*> OverlappingActors;
  
  PressurePlate->GetOverlappingActors(OUT OverlappingActors);
  //iterate through then and add their mass
  for(const auto& Actor : OverlappingActors) {
    float ActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    if (ActorMass)
    {
      TotalMass += ActorMass;
    }
  }
  
  return TotalMass;
}
