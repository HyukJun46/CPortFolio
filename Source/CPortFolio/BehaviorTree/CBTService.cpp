#include "CBTService.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_Girl_AI.h"
#include "Characters/CPlayer.h"

UCBTService::UCBTService()
{

}

void UCBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	if (controller == nullptr) return;

	UCBehaviorComponent* behaviorComp = Cast<UCBehaviorComponent>(controller->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	if (behaviorComp == nullptr) return;

	ACEnemy_Girl_AI* enemy = Cast<ACEnemy_Girl_AI>(controller->GetPawn());
	if (enemy == nullptr) return;

	UCStateComponent* stateComp = Cast<UCStateComponent>(enemy->GetComponentByClass(UCStateComponent::StaticClass()));
	if (stateComp == nullptr) return;

	UCPatrolComponent* patrolComp = Cast<UCPatrolComponent>(enemy->GetComponentByClass(UCPatrolComponent::StaticClass()));
	if (patrolComp == nullptr) return;

	//Hitted
	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	//Get Player from BB
	ACPlayer* player = behaviorComp->GetPlayerKey();

	//No Player
	if (player == nullptr)
	{
		if(patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;
		}

		behaviorComp->SetWaitMode();
		return;
	}



	//Perceived Player
	float distance = enemy->GetDistanceTo(player);

	//-> Is in Attack Range
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//-> Is in Sight Range
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}
}
