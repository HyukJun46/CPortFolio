#include "CAttachment.h"
#include "GameFramework/Character.h"

ACAttachment::ACAttachment()
{
	//Create SceneComponent
	Root = CreateDefaultSubobject<USceneComponent>("Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Super::BeginPlay();
	
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}
