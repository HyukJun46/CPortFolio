#include "CAim.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CHUD.h"

UCAim::UCAim()
{ 
	ConstructorHelpers::FObjectFinder<UCurveFloat> asset(L"CurveFloat'/Game/Player/Curve_Aim.Curve_Aim'");
	verify(asset.Succeeded());

	Curve = asset.Object;
}

void UCAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	SpringArm = Cast<USpringArmComponent>(OwnerCharacter->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (SpringArm == nullptr) return;

	Camera = Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
	if (Camera == nullptr) return;

	OnTimeline.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimeline);
	Timeline.SetPlayRate(10.f);

	UWorld* world = OwnerCharacter->GetWorld();
	if (world == nullptr) return;
	HUD = world->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	if (IsAvailable() == false) return;
	if(bZooming == true) return;

	bZooming = true;
	HUD->EnableAim();

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	Timeline.PlayFromStart();
}

void UCAim::Off()
{
	if (IsAvailable() == false) return;
	if (bZooming == false) return;

	bZooming = false;
	HUD->DisableAim();

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector::ZeroVector;
	SpringArm->bEnableCameraLag = true;

	Timeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}