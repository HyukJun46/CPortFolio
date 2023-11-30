#include "CDoAction_Gun.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CBullet.h"
#include "CAim.h"

void ACDoAction_Gun::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);

	ActionComp = Cast<UCActionComponent>(OwnerCharacter->GetComponentByClass(UCActionComponent::StaticClass()));
	if (ActionComp == nullptr) return;

	ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_Gun::AbortByTypeChanged);
}

void ACDoAction_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_Gun::DoAction()
{
	if((Datas.Num() > 0) == false) return;

	if (Aim->IsAvailable())
		if((Aim->IsZooming())==false)return;

	if((StateComp->IsIdleMode()) == false) return;
	StateComp->SetActionMode();

	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Gun::Begin_DoAction()
{
	if ((Datas[0].ProjectileClass) == nullptr) return;

	FVector location;
	FRotator rotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(location, rotation);

	FVector handSocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Muzzle");
	FVector cameraDirection = rotation.Vector();
	location += cameraDirection * ((handSocketLocation - location) | cameraDirection);

	FTransform transmform = Datas[0].EffectTransform;
	transmform.AddToTranslation(location);
	transmform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));

	ACBullet* Bullet = GetWorld()->SpawnActorDeferred<ACBullet>
		(
			Datas[0].ProjectileClass,
			transmform,
			OwnerCharacter,
			OwnerCharacter,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	Bullet->OnBeginOverlap.AddDynamic(this, &ACDoAction_Gun::OnBulletBeginOverlap);
	Bullet->FinishSpawning(transmform);
}

void ACDoAction_Gun::End_DoAction()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACDoAction_Gun::OnAim()
{
	if(Aim == nullptr) return;

	Aim->On();
}

void ACDoAction_Gun::OffAim()
{
	if (Aim == nullptr) return;

	Aim->Off();
}

void ACDoAction_Gun::OnBulletBeginOverlap(FHitResult hitResult)
{
	FDamageEvent damageEvent;
	hitResult.Actor->TakeDamage
	(
		Datas[0].Power,
		damageEvent,
		OwnerCharacter->GetController(),
		this
	);
}

void ACDoAction_Gun::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	if ((Aim->IsAvailable()) == false) return;
	if ((Aim->IsZooming()) == false) return;
	Aim->Off();
}