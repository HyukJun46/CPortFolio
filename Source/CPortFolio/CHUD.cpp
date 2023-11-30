#include "CHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

ACHUD::ACHUD()
{
	ConstructorHelpers::FObjectFinder<UTexture2D>asset(L"Texture2D'/Game/Player/FirstPersonCrosshair.FirstPersonCrosshair'");
	verifyf(asset.Succeeded(), L"Class Not Found");
	CrosshairTex = asset.Object;
}

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

	if (bVisibleAim == false) return;
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
