// Battle Tank

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle) {
  
  // Clamp actual throttle value so player cant over-drive
  FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
  FVector ForceLocation = GetComponentLocation(); // Location of the Track
  
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation );
}
