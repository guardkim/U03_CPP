#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Tornado.generated.h"

UCLASS()
class U03_GAME_API ACDoAction_Tornado : public ACDoAction
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		float HittedTime = 0.1f;
	UPROPERTY(EditDefaultsOnly)
		float DestroyTime = 5.0f; //파티클이 유지가 될 시간(지속시간)
	UPROPERTY(EditDefaultsOnly)
		float Speed = 300.0f;	//플레이어의 주변을 맴도는 스피드
	UPROPERTY(EditDefaultsOnly)
		float Distance = 150.0f;	//플레이어와 파티클 사이의 거리
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Attached;

protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Abort() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void Hitted();
	UFUNCTION()
		void Finish();

private:
	//부모가 UFUNCTION()이면 자식도 동일
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

private:
	//멤버변수
	class UBoxComponent* Box; //충돌체
	bool bOnce; //Tornado를 한번 시전하면 5초동안 주변을 돌면서 유지된다. 중복사용 방지용
	
	TArray<class ACharacter*> HittedCharacters;
	float Angle; //Yaw회전으로 맴돈다


};
