// Battle Tank

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

  // Move the barrel the right amount this frame
  // Given the max elevation speed, and the frame time
  
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
  
  auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto RawNewElevation = FMath::Clamp<float>( RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
  
  SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}


