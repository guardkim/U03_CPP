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
			DatasAssets[i]->BeginPlay(character, &Datas[i]);//SpawnDefferd된 결과가 UCAtion Datas에 저장됨
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
		Datas[(int32)Type]->GetEquipment()->UnEquip();
	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();
	ChangeType(EActionType::Unarmed); //SetMode를 사용하면 재귀되기 때문에 ChangeType으로 바로 보냄
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
		//칼을 든 상태에서 다시한번 누를때
		SetUnarmedMode();
		return;
	}
	else if (isUnarmedMode() == false)
	{
		if (!!Datas[(int32)Type])
			Datas[(int32)Type]->GetEquipment()->UnEquip();
	}
	if (!!Datas[(int32)InType] && !!Datas[(int32)InType]->GetEquipment()) // 변경하고자 하는 무기
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
	} DoAction_Throw에서 딜리게이트에 바인딩 해줄 함수*/

	if (OnActionTypeChanged.IsBound())// Execute()전에 Binding 되었는지 확인
		OnActionTypeChanged.Broadcast(prevType, Type); // Delegate에 Binding 된 함수들을 실행
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
	OffAllCollision(); //무기 충돌체 끄기
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
		//칼을 꺼내다 맞으면 칼을 강제로 붙여주고, Idle로 바꿔줌
		Datas[(int32)Type]->GetEquipment()->Begin_Equip();
		Datas[(int32)Type]->GetEquipment()->End_Equip();
	}
	if (!!Datas[(int32)Type]->GetDoAction())
	{
		//그 외 추가로 필요한 내용이 있으면 Abort에 작성
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