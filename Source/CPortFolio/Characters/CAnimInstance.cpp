#include "CAnimInstance.h"
#include "CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* OwnerPawn = TryGetPawnOwner();
	if (OwnerPawn == nullptr) return;

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner();
	//CheckNull
	if (OwnerPawn == nullptr) return;

	Speed = OwnerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerPawn->GetVelocity(), OwnerPawn->GetControlRotation());
}
