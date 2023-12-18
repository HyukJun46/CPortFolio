#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChangedSignature, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public: // Get Behavior from BlackBoard
	UFUNCTION(BlueprintCallable)
		bool IsWaitMode();

	UFUNCTION(BlueprintCallable)
		bool IsApproachMode();

	UFUNCTION(BlueprintCallable)
		bool IsActionMode();

	UFUNCTION(BlueprintCallable)
		bool IsPatrolMode();

	UFUNCTION(BlueprintCallable)
		bool IsHittedMode();

private:
	EBehaviorType GetTypeFromBB();

public: //Set Behavior To BlackBoard
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();

	class ACPlayer* GetPlayerKey();
	FVector GetLocationKey();

private:
	void ChangeType(EBehaviorType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChangedSignature OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "BehaviorKey";

	UPROPERTY(EditAnywhere)
		FName  PlayerKey = "PlayerKey";

	UPROPERTY(EditAnywhere)
		FName LocationKey = "LocationKey";

private:
	class UBlackboardComponent* Blackboard;
};
