#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrow.generated.h"

UCLASS()
class U03_GAME_API ACThrow : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion; //맞는쪽 파티클
	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform; //맞는 위치 보정
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere; // 충돌체
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle; //날아다니는 파티클
	UPROPERTY(EditDefaultsOnly) 
		class UProjectileMovementComponent* Projectile; //발사체
public:	
	ACThrow();

protected:
	virtual void BeginPlay() override;

};
