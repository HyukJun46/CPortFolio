#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h" //EnumType is Not Forward Declaration
#include "CPlayer.generated.h"

UCLASS()
class CPORTFOLIO_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Move
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	//Mouse
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
	void OnZoom(float Axis);

private:
	//Sprint
	void OnSprint();
	void OffSprint();
	//Roll
	void OnRoll();
	//Fist
	void OnFist();
	//Sword
	void OnSword();
	//Gun
	void OnGun();
	//Action
	void OnAttack();

private:
	void Begin_Roll();

public:
	void End_Roll(); //Notify Not Private

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	//Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:
	//Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;
};
