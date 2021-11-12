#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	//���� Ŭ��(���ݽ�)
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);

	if (bEnable == true)
	{
		//bEnable ��뱸��(�޺��������� Ŭ����)
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

	//�޺� ��뱸�� ���� Ŭ�� �� �� ������ PlayNextCombo��Ƽ����
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
	// ������ Attacked��Ƽ����
	Super::End_DoAction(); 

	OwnerCharacter->StopAnimMontage(Datas[Index].AnimMontage);
	Index = 0;
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//�浹�Ǹ� ���� �� ��
	Super::OnAttachmentBeginOverlap(InAttacker,InAttackCauser,InOtherCharacter); 

	//�ߺ�Ÿ�� ����
	for (const ACharacter* other : HittedCharacter)
	{
		if (other == InOtherCharacter)
		return;
	}
	HittedCharacter.Add(InOtherCharacter);
	FDamageEvent e; //TODO : Damage �̺�Ʈ ����...
	InOtherCharacter->TakeDamage(Datas[Index].Power,e,InAttacker->GetController(),InAttackCauser); 
	//��ü ���� TakeDamage �Լ��� �ۼ��ϸ� �������� �ִ��� �޴����� �������ϸ��
	//InOtherCharacter == �浹�� ���� (Enemy) ���� Enemy�� ������ �� TakeDamage�� ���̵�

}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	//Ÿ�� ����
	HittedCharacter.Empty();
}
