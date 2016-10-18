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
  
  
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  
  
  /// OUT means this variables will be modified by the function.
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                             OUT PlayerViewPointLocation,
                                                             OUT PlayerViewPointRotation
                                                             );
  
  
  /// Draw a red trace in the world to visualise
  FVector PlayerReachEndOfLine = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
  
  
  // if the physics handle is attached
  if(PhysicsHandle->GrabbedComponent) {
    //move the object  that we are holding
    PhysicsHandle->SetTargetLocation(PlayerReachEndOfLine);
  }
  
  // ...
  
  
  
}


void UGrabber::FindPhysicsHandleComponent() {
  // Look for attached Physics Handle
  // Generic signature inside <type> Find Component of type <> inside Owner.
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if(PhysicsHandle) {
    
    
  }else {
    UE_LOG(LogTemp, Error, TEXT("Missing physicHandle Component for %s"), *GetOwner()->GetName());
  }
}

void UGrabber::SetupInputComponent() {
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if(InputComponent) {
    UE_LOG(LogTemp, Warning, TEXT("Found UIInputComponent"));
    
    /// Bind the input axis
    InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    
    
  }else {
    UE_LOG(LogTemp, Error, TEXT("Missing Input Component for %s"), *GetOwner()->GetName());
  }
}

void UGrabber::Grab() {
  
  // Line trace and see if we are in reach
  UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
  GetFirstPhysicsBodyInReach();
  
  auto HitResult = GetFirstPhysicsBodyInReach();
  auto ComponentToGrab = HitResult.GetComponent();
  auto ActorHit = HitResult.GetActor();
  
  // if we hit something then attach a physic handle
  if(ActorHit) {
    PhysicsHandle->GrabComponent(
                                 ComponentToGrab,
                                 NAME_None,
                                 ComponentToGrab->GetOwner()->GetActorLocation(),
                                 true // allow rotation
                                 );
  }
}

void UGrabber::Release() {
  UE_LOG(LogTemp, Warning, TEXT("Grabbing released"));
  PhysicsHandle->ReleaseComponent();
  
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  
  
  /// OUT means this variables will be modified by the function.
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                             OUT PlayerViewPointLocation,
                                                             OUT PlayerViewPointRotation
                                                             );
  
  
  /// Draw a red trace in the world to visualise
  FVector PlayerReachEndOfLine = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
  
  //  DrawDebugLine(GetWorld(),
  //                PlayerViewPointLocation,
  //                PlayerReachEndOfLine,
  //                FColor(255,0,0),
  //                false,
  //                0.f,
  //                0.f,
  //                10.0f );
  
  FHitResult Hit;
  
  // Setup query params
  FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
  
  // Line trace (AKA ray-cast) out to reach distance
  GetWorld()->LineTraceSingleByObjectType(OUT Hit,
                                          PlayerViewPointLocation,
                                          PlayerReachEndOfLine,
                                          FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                          TraceParameters);
  
  
  /// See what we hit
  
  AActor* ActorHit = Hit.GetActor();
  if(ActorHit) {
    UE_LOG(LogTemp, Warning, TEXT("line trace hit: %s"), *(ActorHit->GetName()))
  }
  
  return Hit;
}


