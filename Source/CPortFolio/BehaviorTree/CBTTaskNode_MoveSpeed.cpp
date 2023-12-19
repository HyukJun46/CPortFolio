#include "CBTTaskNode_MoveSpeed.h"
#include "AIController.h"
#include "Characters/CEnemy_Girl.h"

UCBTTaskNode_MoveSpeed::UCBTTaskNode_MoveSpeed()
{
    NodeName = "MoveSpeed";
}

EBTNodeResult::Type UCBTTaskNode_MoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    AAIController* controller = OwnerComp.GetAIOwner();
    if (controller == nullptr) return EBTNodeResult::Failed;

    ACEnemy_Girl* enemy = Cast<ACEnemy_Girl>(controller->GetPawn());
    if (enemy == nullptr) return EBTNodeResult::Failed;

    UCStatusComponent* statusComp = Cast<UCStatusComponent>(enemy->GetComponentByClass(UCStatusComponent::StaticClass()));
    if (statusComp == nullptr) return EBTNodeResult::Failed;

    statusComp->ChangeMoveSpeed(Type);

    return EBTNodeResult::Succeeded;
}