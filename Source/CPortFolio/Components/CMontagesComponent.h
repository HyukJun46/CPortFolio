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
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

private:
	FMontageData* MontageDatas[(int32)EStateType::Max];
		
};