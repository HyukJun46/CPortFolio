#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm
	//SceneComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//ActorComponent
	Status = CreateDefaultSubobject<UCStatusComponent>("Status");
	Option = CreateDefaultSubobject<UCOptionComponent>("Option");
	State = CreateDefaultSubobject<UCStateComponent>("State");
	Montages = CreateDefaultSubobject<UCMontagesComponent>("Montages");

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

