#include "CAnimNotify_EndAction.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CDoAction.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr)return;
	if (MeshComp->GetOwner() == nullptr)return;

	UCActionComponent* actionComp = Cast<UCActionComponent>((MeshComp->GetOwner())->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	UCActionData* currentData = actionComp->GetCurrentData();
	if (currentData == nullptr) return;

	ACDoAction* doAction = currentData->GetDoAction();
	if (doAction == nullptr) return;

	doAction->End_DoAction();

}