// Battle Tank

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed) {
  
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
  auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto Yaw = RelativeRotation.Yaw + RotationChange;
  
  SetRelativeRotation(FRotator(0, Yaw, 0));
}
