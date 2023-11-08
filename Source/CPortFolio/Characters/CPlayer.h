#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	//MoveEvent
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

private:
	//Sprint
	void OnSprint();
	void OffSprint();

private:
	//Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	//Mouse
	UPROPERTY(EditAnywhere, Category = "Mouse")
		float HorizontalSpeed = 45.f;
	UPROPERTY(EditAnywhere, Category = "Mouse")
		float VerticalSpeed = 45.f;

private:
	//Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
};
