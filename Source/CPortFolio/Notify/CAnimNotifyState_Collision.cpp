#include "CAnimNotifyState_Collision.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction_Melee.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData_Spawned* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACAttachment* attachment = currData->GetAttachment();
	if (attachment == nullptr) return;

	attachment->OnCollisions();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData_Spawned* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACAttachment* attachment = currData->GetAttachment();
	if (attachment == nullptr) return;

	attachment->OffCollisions();

	ACDoAction_Melee* doAction_Melee = Cast<ACDoAction_Melee>(currData->GetDoAction());
	if (doAction_Melee == nullptr) return;
	doAction_Melee->ClearHittedCharacters();

}
