#include "CEnvQueryContext_Player.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	ACEnemy_AI* aiObject = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());//weak������ ���� GEt�� ����� �ּҰ� ���´�(Enemy ��ü�� ���� �ּ�����)
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(aiObject->GetController());//Behavior�� Pawn�� �ٴ°Ծƴ϶� AIController�� �پ��ִ�
	if(!!behavior->GetTargetPlayer())
		UEnvQueryItemType_Actor::SetContextHelper(ContextData,behavior->GetTargetPlayer()); //�÷��̾� �߽����� ���� �׷������Ѵ�.
}