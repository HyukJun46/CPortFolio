#include "CEquipment.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	//Get Component
	StateComp = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	StatusComp = Cast<UCStatusComponent>(OwnerCharacter->GetComponentByClass(UCStatusComponent::StaticClass()));
}

void ACEquipment::Equip_Implementation()
{
	//Set State Equip
	StateComp->SetEquipMode();

	//bCanMove
	Data.bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	//Play Draw AnimMontage
	if(!!Data.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	//bPawnController
	if (Data.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACEquipment::Unequip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}
