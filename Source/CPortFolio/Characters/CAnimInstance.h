#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class CPORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected: // BlueprintReadOnly should not be used on private members
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "OwnerCharacter")
		float Direction;
};
