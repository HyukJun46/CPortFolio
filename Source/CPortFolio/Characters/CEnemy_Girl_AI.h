#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy_Girl.h"
#include "CEnemy_Girl_AI.generated.h"

UCLASS()
class CPORTFOLIO_API ACEnemy_Girl_AI : public ACEnemy_Girl
{
	GENERATED_BODY()

public:
	ACEnemy_Girl_AI();

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCPatrolComponent* Patrol;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;
};
