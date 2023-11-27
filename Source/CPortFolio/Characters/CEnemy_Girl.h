#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy_Girl.generated.h"

UCLASS()
class CPORTFOLIO_API ACEnemy_Girl : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemy_Girl();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
};
