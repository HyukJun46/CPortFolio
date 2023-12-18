#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actions/CActionData.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm
	//SceneComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//ActorComponent
	Action = CreateDefaultSubobject<UCActionComponent>("Action");
	Montages = CreateDefaultSubobject<UCMontagesComponent>("Montages");
	Status = CreateDefaultSubobject<UCStatusComponent>("Status");
	State = CreateDefaultSubobject<UCStateComponent>("State");
	Option = CreateDefaultSubobject<UCOptionComponent>("Option");

	//Component Settings(SkeletalMesh)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Mixamo/Ch15_nonPBR.Ch15_nonPBR'"));
	if (meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//Animinstance
	//GetClass
	TSubclassOf<UAnimInstance> animClass;
	ConstructorHelpers::FClassFinder<UAnimInstance> asset(TEXT("AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'"));
	if (asset.Succeeded()) animClass = asset.Class;
	GetMesh()->SetAnimInstanceClass(animClass);

	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 40));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 240.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	Camera->SetupAttachment(SpringArm);

	//Move Setting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

	Action->SetUnarmedMode();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Move(Axis)
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	//Action
	//Sprint
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
	//Roll
	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::OnRoll);
	//Fist
	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist);
	//Sword
	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, this, &ACPlayer::OnSword);
	//Gun
	PlayerInputComponent->BindAction("Gun", EInputEvent::IE_Pressed, this, &ACPlayer::OnGun);
	//Action
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACPlayer::OnAttack);
	//Aim
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(PlayerTeamID);
}

void ACPlayer::OnMoveForward(float Axis)
{
	//CheckTrue
	if (FMath::IsNearlyZero(Axis) == true) return;
	if (Status->IsCanMove() == false) return;

	//Forward
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	//CheckTrue
	if (FMath::IsNearlyZero(Axis) == true) return;
	if (Status->IsCanMove() == false) return;

	//Right
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	float speed = Option->GetHorizontalSpeed();
	AddControllerYawInput(speed * Axis * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float Axis)
{
	float speed = Option->GetVerticalSpeed();;
	AddControllerPitchInput(speed * Axis * GetWorld()->GetDeltaSeconds());

}

void ACPlayer::OnZoom(float Axis)
{
	float rate = Option->GetZoomSpeed() * Axis * GetWorld()->GetDeltaSeconds();
	SpringArm->TargetArmLength += rate;
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();
}

void ACPlayer::OnRoll()
{
	if (State->IsIdleMode() == false) return;

	State->SetRollMode();
}

void ACPlayer::OnFist()
{
	if(State->IsIdleMode() == false) return;

	Action->SetFistMode();
}

void ACPlayer::OnSword()
{
	if (State->IsIdleMode() == false) return;

	Action->SetSwordMode();
}

void ACPlayer::OnGun()
{
	if (State->IsIdleMode() == false) return;

	Action->SetGunMode();
}

void ACPlayer::OnAttack()
{
	Action->DoAction();
}

void ACPlayer::OnAim()
{
	Action->DoAim(true);
}

void ACPlayer::OffAim()
{
	Action->DoAim(false);
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector target = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));

	Montages->PlayRoll();
}

void ACPlayer::End_Roll()
{
	if (Action->GetCurrentData()->EquipmentData.bPawnControl == true)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

	}

	State->SetIdleMode();
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Roll:	Begin_Roll();	break;
	}
}

