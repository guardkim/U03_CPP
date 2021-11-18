#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter, class UCAction** OutAction)
{
	FTransform transform;

	ACAttachment* Attachment = nullptr; //지역변수에 저장
	ACEquipment* Equipment = nullptr;

	if (!!AttachmentClass)
	{
		//L밸류 R밸류 검색...
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(GetLabelName(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}
	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass,transform, InOwnerCharacter);
		// 메모리에 올라가지만 BeginPlay는 호출 안됨 주로 순서 제어때 사용한다.
		Equipment->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(GetLabelName(InOwnerCharacter, "Equipment"));
		UGameplayStatics::FinishSpawningActor(Equipment,transform); // 메모리에 올라간 Equipment를 확정스폰(BeginPlay를 호출)
		
		if (!!AttachmentClass)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}

	ACDoAction* DoAction = nullptr; // 지역변수 저장
	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);
		DoAction->AttachToComponent(InOwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		DoAction->SetData(DoActionDatas);
		DoAction->SetActorLabel(GetLabelName(InOwnerCharacter, "DoAction"));
		UGameplayStatics::FinishSpawningActor(DoAction, transform);

		if (!!Equipment)
		{
			DoAction->SetEquipped(Equipment->GetEquipped());// Equippment의 bEquipped가 적용됌
		}
		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction,&ACDoAction::OnAttachmentBeginOverlap); // 자식에서 재정의
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction,&ACDoAction::OnAttachmentEndOverlap);
		}
	}
	*OutAction = NewObject<UCAction>(); // 주소할당 받음 Hip영역
	(*OutAction)->Attachment = Attachment;
	(*OutAction)->Equipment = Equipment;
	(*OutAction)->DoAction = DoAction;
	(*OutAction)->EquipmentColor = EquipmentColor; // CAction.h의 멤버변수에 저장됨

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
