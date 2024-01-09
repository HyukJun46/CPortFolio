#include "CPlayerHealthWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Characters/CPlayer.h"
#include "Components/CStatusComponent.h"

void UCPlayerHealthWidget::NativeConstruct()
{
	if (CircleGuage == nullptr) return;
	Material = CircleGuage->GetDynamicMaterial();
	if (Material == nullptr) return;

	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	if (player == nullptr) return;

	StatusComp = Cast<UCStatusComponent>(player->GetComponentByClass(UCStatusComponent::StaticClass()));
	if (StatusComp == nullptr) return;

	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());

	if (CurrentHealthText == nullptr) return;
	FString currentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(currentHealthStr));

	Super::NativeConstruct();
}

void UCPlayerHealthWidget::UpdateHealth_Implementation()
{
	if (Material == nullptr) return;
	if (StatusComp == nullptr) return;
	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());

	if (CurrentHealthText == nullptr) return;
	FString currentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(currentHealthStr));

	PlayAnimationForward(DecreaseImpact);
}
