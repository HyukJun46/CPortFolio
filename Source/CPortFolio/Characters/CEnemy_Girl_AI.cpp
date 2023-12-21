#include "CEnemy_Girl_AI.h"
#include "Components/CPatrolComponent.h"

ACEnemy_Girl_AI::ACEnemy_Girl_AI()
{
	Patrol = this->CreateDefaultSubobject<UCPatrolComponent>("Patrol");
}