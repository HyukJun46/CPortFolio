#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UUStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUStateComponent();

protected:
	virtual void BeginPlay() override;

		
};
