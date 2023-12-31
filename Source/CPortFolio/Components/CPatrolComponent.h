#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE bool IsPathValid() { return Path != nullptr; }

	bool GetMoveToLocation(FVector& OutLocation);
	void UpdateNextIndex();

public:	
	UPROPERTY(EditInstanceOnly)
		class ACPatrolPath* Path;

	UPROPERTY(EditAnywhere)
		bool bReverse;

	UPROPERTY(EditAnywhere)
		int32 Index;
};
