#include "CDoAction_Melee.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	if ((Datas.Num() > 0) == false) return;

	//Combo Attack
	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucced = true;

		return;
	}

	if(StateComp->IsIdleMode() == false) return;
	StateComp->SetActionMode();

	//Action MontagePlay
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	if (bSucced == false) return;
	bSucced = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCount].AnimMontage);
	ComboCount = 0;

	//Notify(Idle)
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Melee::OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	//Multi Hit X
	int32 hittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);

	if (hittedCharactersNum < HittedCharacters.Num())
	{
		FDamageEvent damageEvent;
		InOtherCharacter->TakeDamage(Datas[ComboCount].Power, damageEvent, InAttacker->GetController(), InCauser);
	}
}

void ACDoAction_Melee::OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnEndOverlap(InAttacker, InCauser, InOtherCharacter);
}
