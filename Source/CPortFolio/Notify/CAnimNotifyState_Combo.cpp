#include "CAnimNotifyState_Combo.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction_Melee.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACDoAction_Melee* doAction_melee = Cast<ACDoAction_Melee>(currData->GetDoAction());
	if (doAction_melee == nullptr) return;
	doAction_melee->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACDoAction_Melee* doAction_melee = Cast<ACDoAction_Melee>(currData->GetDoAction());
	if (doAction_melee == nullptr) return;
	doAction_melee->DisableCombo();
}
