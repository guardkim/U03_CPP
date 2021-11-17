#include "CThrow.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
ACThrow::ACThrow()
{
	CHelpers::CreateComponent(this, &Sphere, "Sphere");
	CHelpers::CreateComponent(this, &Particle, "Particle", Sphere);
	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 4000.0f;
	Projectile->MaxSpeed = 8000.0f;
	Projectile->ProjectileGravityScale = 0.0f;

}


void ACThrow::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACThrow::OnComponentBeginOverlap);
	
	
}

void ACThrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner());
	if (!!Explosion)
	{

		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(bFromSweep ? SweepResult.Location : GetActorLocation());//상대좌표
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation())); // (ImpactNormal)충돌된 내각에 대한 방향을 리턴
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Explosion,transform);
	}
	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(SweepResult);
	Destroy(); // Destroy하면 처음 충돌시 사라지고 없으면 관통하면서 3초후에 사라짐
}


