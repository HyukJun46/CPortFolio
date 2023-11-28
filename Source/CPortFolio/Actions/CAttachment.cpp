#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	//Create SceneComponent
	Root = CreateDefaultSubobject<USceneComponent>("Root");
}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	GetComponents<UShapeComponent>(Collisions);

	for (const auto& collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::BeginOverlap);
		collision->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::EndOverlap);
	}

	OffCollisions();



	Super::BeginPlay();
	
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToComp(USceneComponent* InComponent, FName InSocketName)
{
	InComponent->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACAttachment::OnCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACAttachment::OffCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACAttachment::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if((OwnerCharacter == OtherActor) == true) return;

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

	if (OnBeginOverlap.IsBound())
	{
		if (!!otherCharacter)
			OnBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void ACAttachment::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OwnerCharacter == OtherActor) == true) return;

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

	if (OnEndOverlap.IsBound())
	{
		if (!!otherCharacter)
			OnEndOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}
