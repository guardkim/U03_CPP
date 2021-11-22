#include "CEnvQueryContext_Player.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	ACEnemy_AI* aiObject = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());//weak포인터 여서 GEt을 해줘야 주소가 나온다(Enemy 객체에 대한 주소참조)
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(aiObject->GetController());//Behavior는 Pawn에 붙는게아니라 AIController에 붙어있다
	if(!!behavior->GetTargetPlayer())
		UEnvQueryItemType_Actor::SetContextHelper(ContextData,behavior->GetTargetPlayer()); //플레이어 중심으로 원이 그려져야한다.
}
