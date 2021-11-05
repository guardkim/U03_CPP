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
	ChangeType(InType);
}
void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())// Execute()전에 Binding 되었는지 확인
		OnActionTypeChanged.Broadcast(prevType, Type); // Delegate에 Binding 된 함수들을 실행
}