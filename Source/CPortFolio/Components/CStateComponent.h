#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll, Equip, Action, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChangedSignature, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	//Get State
	UFUNCTION(BlueprintPure)
		bool IsIdleMode() { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		bool IsRollMode() { return Type == EStateType::Roll; }
	
	UFUNCTION(BlueprintPure)
		bool IsEquipMode() { return Type == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
		bool IsActionMode() { return Type == EStateType::Action; }

public:
	EStateType GetType() { return Type; }

public:
	void SetIdleMode();
	void SetRollMode();
	void SetEquipMode();
	void SetActionMode();

public:
	void ChangeType(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;
		
};
