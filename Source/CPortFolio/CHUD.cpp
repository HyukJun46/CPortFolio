#include "CHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	//player->ActionComp->Type => FString => Print
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter == nullptr) return;

	StateComp = Cast<UCStateComponent>(playerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));

	StateTypeEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStateType"), true);
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	//Print Player StateType
	if (StateComp == nullptr) return;
	if (StateTypeEnum == nullptr) return;

	FString typeStr = StateTypeEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Black, 10, Canvas->ClipY - 50, nullptr, 1.5f);
}
