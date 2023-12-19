#include "CBTTaskNode_Action.h"
#include "AIController.h"
#include "Characters/CEnemy_Girl.h"
#include "Components/CActionComponent.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

    bNotifyTick = true;
}


EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
    AAIController* controller = OwnerComp.GetAIOwner();
    if (controller == nullptr) return EBTNodeResult::Failed;

    ACEnemy_Girl* enemy = Cast<ACEnemy_Girl>(controller->GetPawn());
    if (enemy == nullptr) return EBTNodeResult::Failed;

    UCActionComponent* actionComp = Cast<UCActionComponent>(enemy->GetComponentByClass(UCActionComponent::StaticClass()));
    if (actionComp == nullptr) return EBTNodeResult::Failed;

    RunningTime = 0.f;
    actionComp->DoAction();

    return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* controller = OwnerComp.GetAIOwner();
    if (controller == nullptr) return;

    ACEnemy_Girl* enemy = Cast<ACEnemy_Girl>(controller->GetPawn());
    if (enemy == nullptr) return;

    UCStateComponent* stateComp = Cast<UCStateComponent>(enemy->GetComponentByClass(UCStateComponent::StaticClass()));
    if (stateComp == nullptr) return;

    RunningTime += DeltaSeconds;


    if (stateComp->IsIdleMode() && RunningTime >= Delay)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
