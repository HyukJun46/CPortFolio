#include "CEnemy_Girl.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

ACEnemy_Girl::ACEnemy_Girl()
{
	PrimaryActorTick.bCanEverTick = true;

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
}

void ACEnemy_Girl::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACEnemy_Girl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

