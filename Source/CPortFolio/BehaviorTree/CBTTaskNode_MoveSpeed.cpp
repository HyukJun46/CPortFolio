#include "CBTTaskNode_MoveSpeed.h"
#include "AIController.h"
#include "Characters/CEnemy_Girl.h"

UCBTTaskNode_MoveSpeed::UCBTTaskNode_MoveSpeed()
{
    NodeName = "MoveSpeed";
}

EBTNodeResult::Type UCBTTaskNode_MoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

}