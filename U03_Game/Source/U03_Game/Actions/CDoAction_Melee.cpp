#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	//왼쪽 클릭(공격시)
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);

	if (bEnable == true)
	{
		//bEnable 허용구간(콤보구간에서 클릭시)
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}
void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	//콤보 허용구간 내에 클릭 할 시 블프때 PlayNextCombo노티파이
	CheckFalse(bExist)
	bExist = false;

	OwnerCharacter->StopAnimMontage();

	Index++;
	Index = FMath::Clamp<int32>(Index, 0, Datas.Num() - 1);
	OwnerCharacter->PlayAnimMontage(Datas[Index].AnimMontage, Datas[Index].PlayRate, Datas[Index].StartSection);
	Datas[Index].bCanMove ? Status->SetMove() : Status->SetStop();

}


void ACDoAction_Melee::End_DoAction()
{
	// 블프때 Attacked노티파이
	Super::End_DoAction(); 

	OwnerCharacter->StopAnimMontage(Datas[Index].AnimMontage);
	Index = 0;
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//충돌되면 실행 될 곳
	Super::OnAttachmentBeginOverlap(InAttacker,InAttackCauser,InOtherCharacter); 

	//중복타격 방지
	for (const ACharacter* other : HittedCharacter)
	{
		if (other == InOtherCharacter)
		return;
	}
	HittedCharacter.Add(InOtherCharacter);
	FDamageEvent e; //TODO : Damage 이벤트 공부...
	InOtherCharacter->TakeDamage(Datas[Index].Power,e,InAttacker->GetController(),InAttackCauser); 
	//객체 없이 TakeDamage 함수를 작성하면 데미지를 주는쪽 받는쪽은 재정의하면됨
	//InOtherCharacter == 충돌된 액터 (Enemy) 따라서 Enemy에 재정의 된 TakeDamage가 콜이됨

}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	//타수 종료
	HittedCharacter.Empty();
}
