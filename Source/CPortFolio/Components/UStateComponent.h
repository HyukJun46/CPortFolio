#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Roll
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChangedSignature, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UUStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	//Get State
	UFUNCTION(BlueprintPure)
		bool IsIdleMode() { return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
		bool IsIdleMode() { return Type == EStateType::Roll; }
	
public:
	void SetIdleMode();
	void SetRollMode();

public:
	void ChangeType(EStateType InNewType);

public:
	FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;
		
};
