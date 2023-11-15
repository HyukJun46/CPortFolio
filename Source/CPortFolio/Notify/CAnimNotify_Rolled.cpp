#include "CAnimNotify_Rolled.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_Rolled::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCAnimNotify_Rolled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp == nullptr)return;
	if (MeshComp->GetOwner() == nullptr)return;

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	if (player == nullptr) return;

	player->End_Roll();
}