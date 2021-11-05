#include "CActionComponent.h"
#include "Global.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCActionComponent::SetUnarmedMode()
{
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
	ChangeType(InType);
}
void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())// Execute()���� Binding �Ǿ����� Ȯ��
		OnActionTypeChanged.Broadcast(prevType, Type); // Delegate�� Binding �� �Լ����� ����
}