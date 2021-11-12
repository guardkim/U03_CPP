#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class U03_GAME_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	//부모클래스에서 UFUNCTION()을 지정해놨으면 자식도 자동으로 적용됨
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
private:
	int32 Index; //Combo Count

	//콤보 허용 구간
	bool bEnable; //첫 공격 클릭 시 true , 구간이 끝날경우 false
	bool bExist; // bEnable 구간 안에서 한번 더 공격 클릭시 true, bEnable 구간 안에서 클릭하지 않을시 false 다음콤보로 이어지지않음
	bool bLast; // 콤보의 마지막 구간인지

	TArray<class ACharacter*> HittedCharacter;


	
};
