#include "UStateComponent.h"

UUStateComponent::UUStateComponent()
{
}

void UUStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UUStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UUStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UUStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(Type, InNewType);
}
