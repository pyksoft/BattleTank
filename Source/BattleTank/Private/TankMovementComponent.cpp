// Battle Tank

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet,UTankTrack* RightTrackToSet) {
 
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
  
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
  // No need to call super as we overriding the method.
  FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
  
  float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
  float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
  
  IntendMoveForward(ForwardThrow);
  IntendTurnRight(RightThrow);

}

void UTankMovementComponent::IntendMoveForward(float Throw){
  if(!ensure(LeftTrack && RightTrack)) {
    return;
  }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw){
  if(!ensure(LeftTrack && RightTrack)) {
    return;
  }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}
