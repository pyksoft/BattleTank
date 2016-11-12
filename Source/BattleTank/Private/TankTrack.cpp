// Battle Tank

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
  PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay(){
  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle) {
  
  CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
  
}

void UTankTrack::DriveTrack() {
  // Clamp actual throttle value so player cant over-drive
  FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
  FVector ForceLocation = GetComponentLocation(); // Location of the Track
  
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation );

}


void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
    
  // Drive the tracks.
  DriveTrack();
  
  // Apply sideways force
  ApplySidewaysForce();
  
  // Reset Throttle
  CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce() {
  // Calculate the slippage speed
  if(!ensure( GetOwner() )) {return; }
  
  float DeltaTime = GetWorld()->GetDeltaSeconds();
  
  if(!ensure( DeltaTime )) {return; }
  
  
  float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
  
  // Work out the required acceleration this frame to correct
  FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
  
  // Calculate and applied sideways force (F = m * a)
  auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
  FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
  
  TankRoot->AddForce(CorrectionAcceleration);
  
  
};
