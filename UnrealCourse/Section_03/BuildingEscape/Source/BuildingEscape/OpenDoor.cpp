// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
  
  OwnerPointer = GetOwner();
}




// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
  
  ActorPointerThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

  
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
  
  // Poll the triigger volume every frame
  // if the ActorPointerThatOpens is in volume
  if(PressurePlate->IsOverlappingActor(ActorPointerThatOpens)) {
    OpenDoor();
    LastDoorOpenTime = GetWorld()->GetTimeSeconds();
  }
  
  // Check if it is time to close the door.
  if(GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay) {
    CloseDoor();
  }
 
  
}


void UOpenDoor::OpenDoor() {
  // Find the owning actor
  
  
  // Create a rotator
  FRotator Rotation =  FRotator(0.0f, OpenDoorAngle ,0.0f);
  
  
  // Set the door rotation
  
  OwnerPointer->SetActorRotation(Rotation);
}

void UOpenDoor::CloseDoor() {
  // Find the owning actor
  
  
  // Create a rotator
  FRotator Rotation =  FRotator(0.0f, CloseDoorAngle, 0.0f);
  
  
  // Set the door rotation
  
  OwnerPointer->SetActorRotation(Rotation);
}