// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
  
  
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// ...
  
  FString ObjectName = GetOwner() -> GetName();
  FString x = FString::FromInt(GetOwner()-> GetActorLocation().X);
  FString y = FString::FromInt(GetOwner()-> GetActorLocation().Y);
  FString z = FString::FromInt(GetOwner()-> GetActorLocation().Z);
  
  FString ObjectPos = "Position x=" + x + " Position y="+ y + " Position z=" + z;
  
  UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
  
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

