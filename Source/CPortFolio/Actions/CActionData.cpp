#include "CActionData.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter, UCActionData_Spawned** OutSpawned)
{
	FTransform transform;

	ACAttachment* Attachment = nullptr;
	if (!!AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Attachment"));

		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}

	ACEquipment* Equipment = nullptr;
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Equipment"));

		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		if (!!Attachment)
		{
			Equipment->OnBeginEquip.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequip.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	ACDoAction* DoAction = nullptr;
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "DoAction"));

		UGameplayStatics::FinishSpawningActor(DoAction, transform);
	
		if (!!Attachment)
		{
			Attachment->OnBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnBeginOverlap);
			Attachment->OnEndOverlap.AddDynamic(DoAction, &ACDoAction::OnEndOverlap);
		}
	}

	(*OutSpawned) = NewObject<UCActionData_Spawned>();
	(*OutSpawned)->Attachment = Attachment;
	(*OutSpawned)->Equipment = Equipment;
	(*OutSpawned)->DoAction = DoAction;
}

FString UCActionData::GetCustomActorLabel(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetName());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");
	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
