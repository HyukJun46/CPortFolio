#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class CPORTFOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

private:
	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.f;

private:
	class ACEnemy_Girl_AI* PossessedEnemy;
	class UAISenseConfig_Sight* Sight;
};