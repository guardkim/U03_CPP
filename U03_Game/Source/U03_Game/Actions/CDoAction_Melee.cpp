#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}
void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//충돌되면 실행 될 곳
	Super::OnAttachmentBeginOverlap(InAttacker,InAttackCauser,InOtherCharacter); 

	FDamageEvent e; //TODO : Damage 이벤트 공부...
	InOtherCharacter->TakeDamage(Datas[Index].Power,e,InAttacker->GetController(),InAttackCauser); 
	//객체 없이 TakeDamage 함수를 작성하면 데미지를 주는쪽 받는쪽은 재정의하면됨
	//InOtherCharacter == 충돌된 액터 (Enemy) 따라서 Enemy에 재정의 된 TakeDamage가 콜이됨

}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);

}
