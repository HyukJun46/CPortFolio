#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy_Girl.h"
#include "CEnemy_Girl_AI.generated.h"

UCLASS()
class CPORTFOLIO_API ACEnemy_Girl_AI : public ACEnemy_Girl
{
	GENERATED_BODY()

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;
};
