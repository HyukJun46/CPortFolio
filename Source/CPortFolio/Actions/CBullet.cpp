#include "CBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ACBullet::ACBullet()
{
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(RootComponent);
	
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Sphere);

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Profectile");

	InitialLifeSpan = 3.f;

	Projectile->InitialSpeed = 2000.f;
	Projectile->MaxSpeed = 4000.f;
	Projectile->ProjectileGravityScale = 0.f;
}
void ACBullet::BeginPlay()
{
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnComponentBeginOverlap);

	Super::BeginPlay();
}

void ACBullet::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if((OtherActor == GetOwner()) == true) return;

	//Play Impact Particle
	if (!!ImpactParticle)
	{
		FTransform transform = ImpactTransform;
		transform.AddToTranslation(GetActorLocation());
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
	}


	//DoAction_MagicBall->TakeDamage
	if (OnBeginOverlap.IsBound())
		OnBeginOverlap.Broadcast(SweepResult);

	Destroy();
}