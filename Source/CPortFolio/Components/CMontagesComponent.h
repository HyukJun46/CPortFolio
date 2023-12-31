#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CStateComponent.h"
#include "CMontagesComponent.generated.h"


//-----------------------------------------------------------------------------
// Struct - MontageData(DataTable RowBase)
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase 
{
	GENERATED_BODY()

public:
	static void Log(const FString& InValue);

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};

//-----------------------------------------------------------------------------
// Class - MontagesComponent
//-----------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayRoll();
	void PlayHitted();

private:
	void PlayAnimMontage(EStateType InStateType);

public:	
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;
	
private:
	FMontageData* Datas[(int32)EStateType::Max];
};
