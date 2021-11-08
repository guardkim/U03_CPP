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
		// �޸𸮿� �ö����� BeginPlay�� ȣ�� �ȵ� �ַ� ���� ��� ����Ѵ�.
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		UGameplayStatics::FinishSpawningActor(Equipment,transform); // �޸𸮿� �ö� Equipment�� Ȯ������(BeginPlay�� ȣ��)

	}
}