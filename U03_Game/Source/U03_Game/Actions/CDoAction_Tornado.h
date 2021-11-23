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
		float DestroyTime = 5.0f; //��ƼŬ�� ������ �� �ð�(���ӽð�)
	UPROPERTY(EditDefaultsOnly)
		float Speed = 300.0f;	//�÷��̾��� �ֺ��� �ɵ��� ���ǵ�
	UPROPERTY(EditDefaultsOnly)
		float Distance = 150.0f;	//�÷��̾�� ��ƼŬ ������ �Ÿ�
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
	//�θ� UFUNCTION()�̸� �ڽĵ� ����
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;

private:
	//�������
	class UBoxComponent* Box; //�浹ü
	bool bOnce; //Tornado�� �ѹ� �����ϸ� 5�ʵ��� �ֺ��� ���鼭 �����ȴ�. �ߺ���� ������
	
	TArray<class ACharacter*> HittedCharacters;
	float Angle; //Yawȸ������ �ɵ���


};
