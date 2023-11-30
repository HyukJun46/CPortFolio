#include "CActionComponent.h"
#include "GameFramework/Character.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"

UCActionComponent::UCActionComponent()
{
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if(!!Datas[i])
			Datas[i]->BeginPlay(ownerCharacter);
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if(!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->Unequip();

	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetSwordMode()
{
	SetMode(EActionType::Sword);
}

void UCActionComponent::SetGunMode()
{
	SetMode(EActionType::Gun);
}

void UCActionComponent::SetGrenadeMode()
{
	SetMode(EActionType::Grenade);
}

void UCActionComponent::DoAction()
{
	if (IsUnarmedMode() == true) return;

	//현재 장착중인 Datas[Type]->GetDoActon()->DoAction();
	if (!!GetCurrentData())
	{
		ACDoAction* doAction = GetCurrentData()->GetDoAction();

		if (!!doAction)
			doAction->DoAction();
	}

}

void UCActionComponent::DoAim(bool InPressed)
{
	if (IsUnarmedMode() == true) return;

	if (!!GetCurrentData())
	{
		ACDoAction* doAction = GetCurrentData()->GetDoAction();

		if (!!doAction)
			InPressed ? doAction->OnAim() : doAction->OffAim();
	}
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	//같은 무기일때
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}
	//Unaremd가 아닌 Type
	else if (IsUnarmedMode() == false)
	{
		if(!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}

	if (!!Datas[(int32)Type] && !!Datas[(int32)InNewType]->GetEquipment())
		Datas[(int32)InNewType]->GetEquipment()->Equip();

	ChangeType(InNewType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, Type);
}
