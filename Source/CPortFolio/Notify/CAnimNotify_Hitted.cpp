#include "CAnimNotify_Hitted.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void UCAnimNotify_Hitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCStateComponent* stateComp = Cast<UCStateComponent>((MeshComp->GetOwner())->GetComponentByClass(UCStateComponent::StaticClass()));
	if (stateComp == nullptr) return;

	stateComp->SetIdleMode();
}