#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Actions/CAction.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "Actions/CAttachment.h"
//#include "Actions/CDoAction_Throw.h"
//#include "Actions/CAim.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (!!DatasAssets[i])
			DatasAssets[i]->BeginPlay(character, &Datas[i]);//SpawnDefferd�� ����� UCAtion Datas�� �����
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
		Datas[(int32)Type]->GetEquipment()->UnEquip();
	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();
	ChangeType(EActionType::Unarmed); //SetMode�� ����ϸ� ��͵Ǳ� ������ ChangeType���� �ٷ� ����
}
void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}
void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}
void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}
void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}
void UCActionComponent::SetTornadoMode()
{
	SetMode(EActionType::Tornado);
}
void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}
void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType)
	{
		//Į�� �� ���¿��� �ٽ��ѹ� ������
		SetUnarmedMode();
		return;
	}
	else if (isUnarmedMode() == false)
	{
		if (!!Datas[(int32)Type])
			Datas[(int32)Type]->GetEquipment()->UnEquip();
	}
	if (!!Datas[(int32)InType] && !!Datas[(int32)InType]->GetEquipment()) // �����ϰ��� �ϴ� ����
		Datas[(int32)InType]->GetEquipment()->Equip();
	ChangeType(InType);
}
void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	/*ACDoAction_Throw* doAction = Cast<ACDoAction_Throw>(Datas[(int32)prevType]->GetDoAction());
	if (!!doAction)
	{
		if (doAction->GetAim()->IsAvaliable())
		{
			if(doAction->GetAim()->InZoom())
				doAction->GetAim()->Off();
		}
	} DoAction_Throw���� ��������Ʈ�� ���ε� ���� �Լ�*/

	if (OnActionTypeChanged.IsBound())// Execute()���� Binding �Ǿ����� Ȯ��
		OnActionTypeChanged.Broadcast(prevType, Type); // Delegate�� Binding �� �Լ����� ����
}
void UCActionComponent::DoAction()
{
	CheckTrue(isUnarmedMode());
	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if(!!action)
			action->DoAction();
	}
}
void UCActionComponent::DoOnAim()
{
	CheckTrue(isUnarmedMode());
	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->OnAim();
	}
}
void UCActionComponent::DoOffAim()
{
	CheckTrue(isUnarmedMode());
	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->OffAim();
	}
}
void UCActionComponent::Dead()
{
	OffAllCollision(); //���� �浹ü ����
}
void UCActionComponent::End_Dead()
{
	for (int32 i = 0 ; i < (int32)EActionType::Max ; i++)
	{
		if (!!Datas[i] && !!Datas[i]->GetAttachment())
			Datas[i]->GetAttachment()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetEquipment())
			Datas[i]->GetEquipment()->Destroy();

		if (!!Datas[i] && !!Datas[i]->GetDoAction())
			Datas[i]->GetDoAction()->Destroy();
	}
}
void UCActionComponent::AbortByDamaged()
{
	CheckNull(Datas[(int32)Type]);
	CheckTrue(isUnarmedMode());

	if (!!Datas[(int32)Type]->GetEquipment())
	{
		//Į�� ������ ������ Į�� ������ �ٿ��ְ�, Idle�� �ٲ���
		Datas[(int32)Type]->GetEquipment()->Begin_Equip();
		Datas[(int32)Type]->GetEquipment()->End_Equip();
	}
	if (!!Datas[(int32)Type]->GetDoAction())
	{
		//�� �� �߰��� �ʿ��� ������ ������ Abort�� �ۼ�
		Datas[(int32)Type]->GetDoAction()->Abort();
	}
}
void UCActionComponent::OffAllCollision()
{
	for (UCAction* data : Datas)
	{
		if (!!data == false) // data == nullptr
			continue;
		if (!!data->GetAttachment() == false)
			continue;

		data->GetAttachment()->OffCollision();
	}
}