#include "CAnimInstance.h"
#include "CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* ownerPawn = TryGetPawnOwner();
	if (ownerPawn == nullptr) return;

	//Get Component
	UCActionComponent* actionComp = Cast<UCActionComponent>(ownerPawn->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	actionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);

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

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}
