#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

public:
	FORCEINLINE float GetSneakSpeed() { return SneakSpeed; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }
	
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE bool IsCanMove() { return bCanMove; }

	void SetMove();
	void SetStop();

	void DecreaseHealth(float InAmount);
	void IncreaseHealth(float InAmount);
	
	FORCEINLINE bool IsDead() { return CurrentHealth <= 0; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float SneakSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float WalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float SprintSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.f;

private:
	bool bCanMove = true;
	float CurrentHealth;
};
