#include "CBTTaskNode_Patrol.h"
#include "AIController.h"
#include "Components/CPatrolComponent.h"
#include "Characters/CEnemy_Girl_AI.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	if (controller == nullptr) return EBTNodeResult::Failed;

	ACEnemy_Girl_AI* enemy = Cast<ACEnemy_Girl_AI>(controller->GetPawn());
	if (enemy == nullptr) return EBTNodeResult::Failed;

	UCPatrolComponent* patrolComp = Cast<UCPatrolComponent>(enemy->GetComponentByClass(UCPatrolComponent::StaticClass()));
	if (patrolComp == nullptr) return EBTNodeResult::Failed;

	if (patrolComp->IsPathValid() == false)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = OwnerComp.GetAIOwner();
	if (controller == nullptr) return;

	ACEnemy_Girl_AI* enemy = Cast<ACEnemy_Girl_AI>(controller->GetPawn());
	if (enemy == nullptr) return;

	UCPatrolComponent* patrolComp = Cast<UCPatrolComponent>(enemy->GetComponentByClass(UCPatrolComponent::StaticClass()));
	if (patrolComp == nullptr) return;

	FVector location;
	patrolComp->GetMoveToLocation(location);

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, AcceptanceRadius);
	if (result == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		patrolComp->UpdateNextIndex();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
