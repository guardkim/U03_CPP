#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"

ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Super::BeginPlay(); // �������Ʈ�� BeginPlay�� �����ϰ� ��
	//1108HW unreal actor lifecycle ����, SpawnActor�� �ڵ带 ���� ������ �ֵ�
	//UE �������÷��� U~~MACRO
	//����Ʈ������ U�� �ٿ��ָ� shared_ptr�̳� weak_ptr�� ��ȯ��
	//unique_ptr, shared_ptr, weak_ptr ����, ����� 
}

void ACEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (!!Data.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnEquipmentDelegate.IsBound())
		OnEquipmentDelegate.Broadcast();
	
}

void ACEquipment::End_Equip_Implementation()
{
	State->SetIdleMode();
}

void ACEquipment::UnEquip_Implementation()
{
}
