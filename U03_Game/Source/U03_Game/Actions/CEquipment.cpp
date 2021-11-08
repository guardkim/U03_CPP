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
	Super::BeginPlay(); // 블루프린트쪽 BeginPlay를 실행하게 됨
	//1108HW unreal actor lifecycle 정리, SpawnActor는 코드를 통해 스폰된 애들
	//UE 가비지컬렉터 U~~MACRO
	//스마트포인터 U를 붙여주면 shared_ptr이나 weak_ptr로 변환됨
	//unique_ptr, shared_ptr, weak_ptr 조사, 사용방법 
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
