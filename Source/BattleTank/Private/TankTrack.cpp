// Battle Tank

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle) {
  
  // Clamp actual throttle value so player cant over-drive
  FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
  FVector ForceLocation = GetComponentLocation(); // Location of the Track
  
  UE_LOG(LogTemp, Warning, TEXT("ForceApplied: %s"), *ForceApplied.ToString());
  UE_LOG(LogTemp, Warning, TEXT("ForceLocation %s"), *ForceLocation.ToString());
  UE_LOG(LogTemp, Warning, TEXT("Throttle %f"), Throttle);
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation );
}
