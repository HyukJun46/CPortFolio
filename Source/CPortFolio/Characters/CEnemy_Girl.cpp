#include "CEnemy_Girl.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CActionComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CapsuleComponent.h"
#include "Widgets/CNameWidget.h"
#include "Widgets/CHealthWidget.h"
#include "Kismet/KismetMathLibrary.h"

ACEnemy_Girl::ACEnemy_Girl()
{
	//Create Scene Component
	NameWidget = CreateDefaultSubobject<UWidgetComponent>("NameWidget");
	NameWidget->SetupAttachment(GetMesh());

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
	HealthWidget->SetupAttachment(GetMesh());

	//Create Actor Component
	Action = CreateDefaultSubobject<UCActionComponent>("Action");
	Montages = CreateDefaultSubobject<UCMontagesComponent>("Montages");
	State = CreateDefaultSubobject<UCStateComponent>("State");
	Status = CreateDefaultSubobject<UCStatusComponent>("Status");

	//Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//Get Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Mixamo/Zombiegirl_W_Kurniawan.Zombiegirl_W_Kurniawan'"));
	if(meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);

	//Get Class
	TSubclassOf<UAnimInstance> animInstanceClass;
	ConstructorHelpers::FClassFinder<UAnimInstance> asset(TEXT("AnimBlueprint'/Game/Enemies/ABP_CEnemy_Girl.ABP_CEnemy_Girl_C'"));
	if (asset.Succeeded()) animInstanceClass = asset.Class;
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();

	// -> WidgetComp
	TSubclassOf<UCNameWidget> nameWidgetClass;
	ConstructorHelpers::FClassFinder<UCNameWidget> nameAsset(TEXT("WidgetBlueprint'/Game/Widgets/WB_Name.WB_Name_C'"));
	if (asset.Succeeded()) nameWidgetClass = nameAsset.Class;
	NameWidget->SetWidgetClass(nameWidgetClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 280));
	NameWidget->SetDrawSize(FVector2D(240, 50));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCHealthWidget> healthWidgetClass;
	ConstructorHelpers::FClassFinder<UCHealthWidget> HealthAsset(TEXT("WidgetBlueprint'/Game/Widgets/WB_Health.WB_Health_C'"));
	if (asset.Succeeded()) healthWidgetClass = HealthAsset.Class;
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 240));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy_Girl::BeginPlay()
{
	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy_Girl::OnStateTypeChanged);

	Super::BeginPlay();

	//Widget Settings
	NameWidget->InitWidget();
	UCNameWidget* nameWidget = Cast<UCNameWidget>(NameWidget->GetUserWidgetObject());
	if (!!nameWidget)
	{
		nameWidget->SetNames(GetController()->GetName(), GetName());
	}

	HealthWidget->InitWidget();
	UCHealthWidget* healthWidget = Cast<UCHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}

}

float ACEnemy_Girl::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();

		return DamageValue;
	}

	State->SetHittedMode();

	return DamageValue;
}

void ACEnemy_Girl::Hitted()
{
	//Apply Health Widget
	UCHealthWidget* healthWidget = Cast<UCHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}

	//Play Hitted Montage
	Montages->PlayHitted();

	//Look At Attacker
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FRotator rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0);
	SetActorRotation(rotation);

	//HitBack
	FVector direction = (start - target).GetSafeNormal();
	LaunchCharacter(direction * LaunchValue * DamageValue, true, false);

}

void ACEnemy_Girl::Dead()
{
	//Widget Visibility Disable
	NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GlobalAnimRateScale = 0.f;

	//Add Force
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = (start - target).GetSafeNormal();
	FVector force = direction * LaunchValue * DamageValue;
	GetMesh()->AddForceAtLocation(force, start);

	//Destroy All(Attachment, Equipment, DoAction...)

}

void ACEnemy_Girl::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted: Hitted();	break;
		case EStateType::Dead:	Dead();	 break;
	}
}


