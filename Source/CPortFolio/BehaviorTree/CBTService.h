#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService.generated.h"

UCLASS()
class CPORTFOLIO_API UCBTService : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
