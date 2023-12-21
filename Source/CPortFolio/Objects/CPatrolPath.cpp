#include "CPatrolPath.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

ACPatrolPath::ACPatrolPath()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->SetupAttachment(Root);
	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(Root);

	Spline->SetRelativeLocation(FVector(0, 0, 30));

	Text->SetRelativeLocation(FVector(0, 0, 120));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetTextRenderColor(FColor::Red);

	Spline->bShouldVisualizeScale = true;
	Spline->ScaleVisualizationWidth = 20.f;
}

void ACPatrolPath::BeginPlay()
{
	Super::BeginPlay();

	Text->SetVisibility(false);
}


void ACPatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Spline->SetClosedLoop(bClosedLoop);
	Text->SetText(GetActorLabel());
}