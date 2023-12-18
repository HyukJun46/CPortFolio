#include "CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/CBehaviorComponent.h"
#include "CEnemy_Girl_AI.h"
#include "CPlayer.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UCBehaviorComponent>("Behavior");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->SetMaxAge(2.f);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<ACEnemy_Girl_AI>(InPawn);
	UseBlackboard(PossessedEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	SetGenericTeamId(PossessedEnemy->GetTeamID());
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(PossessedEnemy->GetBehaviorTree());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACAIController::GetSightRadius() 
{ 
	return Sight->SightRadius; 
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACPlayer* player = nullptr;
	for (const auto& perceivedActor : actors)
	{
		player = Cast<ACPlayer>(perceivedActor);

		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("PlayerKey", player);
}
