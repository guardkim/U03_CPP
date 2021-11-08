#include "CActionData.h"
#include "Global.h"
#include "CEquipment.h"
#include "GameFramework/Character.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass,transform); 
		// 메모리에 올라가지만 BeginPlay는 호출 안됨 주로 순서 제어때 사용한다.
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		UGameplayStatics::FinishSpawningActor(Equipment,transform); // 메모리에 올라간 Equipment를 확정스폰(BeginPlay를 호출)

	}
}