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
		class UParticleSystem* Explosion; //�´��� ��ƼŬ
	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform; //�´� ��ġ ����
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere; // �浹ü
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle; //���ƴٴϴ� ��ƼŬ
	UPROPERTY(EditDefaultsOnly) 
		class UProjectileMovementComponent* Projectile; //�߻�ü
public:	
	ACThrow();

protected:
	virtual void BeginPlay() override;

};
