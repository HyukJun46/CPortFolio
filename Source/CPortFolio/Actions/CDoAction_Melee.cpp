#include "CDoAction_Melee.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	if ((Datas.Num() > 0) == false) return;
	if(StateComp->IsIdleMode() == false) return;

	StateComp->SetActionMode();

	//Action MontagePlay
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	//Notify(Combo..)
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	//Notify(Idle)
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}