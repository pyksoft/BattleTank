// Fill out your copyright notice in the Description page of Project Settings.
#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  bWantsBeginPlay = true;
  PrimaryComponentTick.bCanEverTick = true;
  
  // ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
  Super::BeginPlay();
  
  FindPhysicsHandleComponent();
  SetupInputComponent();
  
  
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
  Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

  if(!PhysicsHandle) {
    return; // prevent crash on runtime if !PhysicsHandle
  }
  
  // if the physics handle is attached
  if(PhysicsHandle->GrabbedComponent) {
    //move the object  that we are holding
    PhysicsHandle->SetTargetLocation(GetPlayerEndOfReachLine());
  }
  
  // ...
  
  
  
}


void UGrabber::FindPhysicsHandleComponent() {
  // Look for attached Physics Handle
  // Generic signature inside <type> Find Component of type <> inside Owner.
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if(PhysicsHandle == nullptr) {
     UE_LOG(LogTemp, Error, TEXT("Missing physicHandle Component for %s"), *GetOwner()->GetName());
  }
}

void UGrabber::SetupInputComponent() {
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if(InputComponent) {
    /// Bind the input axis
    InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
  }else {
    UE_LOG(LogTemp, Error, TEXT("Missing Input Component for %s"), *GetOwner()->GetName());
  }
}

void UGrabber::Grab() {
  
  
  
  if(!PhysicsHandle) {
    return; // prevent crash on runtime if !PhysicsHandle
  }
  
  // Line trace and see if we are in reach
  auto HitResult = GetFirstPhysicsBodyInReach();
  auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
  auto ActorHit = HitResult.GetActor();
  
  // if we hit something then attach a physic handle
  if(ActorHit) {
    PhysicsHandle->GrabComponent(
                                 ComponentToGrab, // mesg
                                 NAME_None, // no bones needed
                                 ComponentToGrab->GetOwner()->GetActorLocation(),
                                 true // allow rotation
                                 );
  }
}

void UGrabber::Release() {
  UE_LOG(LogTemp, Warning, TEXT("Grabbing released"));
  
  
  if(!PhysicsHandle) {
    return; // prevent crash on runtime if !PhysicsHandle
  }
  
  PhysicsHandle->ReleaseComponent();
  
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
  
  FHitResult HitResult;
  
  // Setup query params
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

  // Line trace (AKA ray-cast) out to reach distance
  GetWorld()->LineTraceSingleByObjectType(OUT HitResult,
                                          GetPlayerStartOfReachLine(),
                                          GetPlayerEndOfReachLine(),
                                          FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                          TraceParameters);
  
  return HitResult;
}

FVector UGrabber::GetPlayerStartOfReachLine() {
  
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  
  
  /// OUT means this variables will be modified by the function.
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                             OUT PlayerViewPointLocation,
                                                             OUT PlayerViewPointRotation
                                                             );

  return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayerEndOfReachLine() {
  
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  
  
  /// OUT means this variables will be modified by the function.
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                             OUT PlayerViewPointLocation,
                                                             OUT PlayerViewPointRotation
                                                             );
  
  
  /// Draw a red trace in the world to visualise
  FVector PlayerReachEndOfLine = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
  return PlayerReachEndOfLine;
}


