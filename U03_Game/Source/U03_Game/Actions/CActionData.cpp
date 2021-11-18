#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction)
{
	FTransform transform;

	ACAttachment* Attachment = nullptr; //���������� ����
	ACEquipment* Equipment = nullptr;

	if (!!AttachmentClass)
	{
		//L��� R��� �˻�...
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(GetLabelName(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass,transform, InOwnerCharacter);
		// �޸𸮿� �ö����� BeginPlay�� ȣ�� �ȵ� �ַ� ���� ��� ����Ѵ�.
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(GetLabelName(InOwnerCharacter, "Equipment"));
		UGameplayStatics::FinishSpawningActor(Equipment,transform); // �޸𸮿� �ö� Equipment�� Ȯ������(BeginPlay�� ȣ��)
		
		if (!!AttachmentClass)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}

	ACDoAction* DoAction = nullptr; // �������� ����
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetData(DoActionDatas);
		DoAction->SetActorLabel(GetLabelName(InOwnerCharacter, "DoAction"));
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		if (!!Equipment)
		{
			DoAction->SetEquipped(Equipment->GetEquipped());// Equippment�� bEquipped�� �����
		}
		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction,&ACDoAction::OnAttachmentBeginOverlap); // �ڽĿ��� ������
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction,&ACDoAction::OnAttachmentEndOverlap);
		}
	}
	*OutAction = NewObject<UCAction>(); // �ּ��Ҵ� ���� Hip����
	(*OutAction)->Attachment = Attachment;
	(*OutAction)->Equipment = Equipment;
	(*OutAction)->DoAction = DoAction;
	(*OutAction)->EquipmentColor = EquipmentColor; // CAction.h�� ��������� �����

}

FString UCActionData::GetLabelName(ACharacter* InOwnerCharacter, FString InName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InName);
	name.Append("_");

	name.Append(GetName().Replace(L"DA_",L""));
	return name;
}
