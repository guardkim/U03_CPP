#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory,DeltaSeconds);
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	if (state->IsHittedMode())//적이 맞고있다면
	{
		behavior->SetHittedMode();
		return;
	}
	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr)
	{
		behavior->SetWaitMode();
		return;
	}

	float distance = aiPawn->GetDistanceTo(target); // 적과 나의 거리

	if (distance < controller->GetSightRadius()) // 감지범위 안에 플레이어가 있다면
	{
		behavior->SetApproachMode();
		return;
	}
}
