#include "CAnimNotifyState_Equip.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData_Spawned* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACEquipment* equipment = currData->GetEquipment();
	if (equipment == nullptr) return;

	equipment->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UCActionComponent* actionComp = Cast<UCActionComponent>(MeshComp->GetOwner()->GetComponentByClass(UCActionComponent::StaticClass()));
	if (actionComp == nullptr) return;

	//actionComp->DA[Type]->equipmentobj->Begin_Equip();
	UCActionData_Spawned* currData = actionComp->GetCurrentData();
	if (currData == nullptr) return;

	ACEquipment* equipment = currData->GetEquipment();
	if (equipment == nullptr) return;

	equipment->End_Equip();
}
