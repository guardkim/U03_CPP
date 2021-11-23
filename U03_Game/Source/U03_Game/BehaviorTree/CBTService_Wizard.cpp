#include "CBTService_Wizard.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"

UCBTService_Wizard::UCBTService_Wizard()
{
	NodeName = "Wizard";
}
void UCBTService_Wizard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	CheckTrue(state->IsDeadMode());

	if (state->IsHittedMode())
	{
		behavior->SetHittedMode();
		return;
	}

	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr)
	{
		behavior->SetWaitMode();
		controller->ClearFocus(EAIFocusPriority::Gameplay); //적이 계속 쳐다보지 않게 한번 날려줌
		return;
	}
	else
	{
		//플레이어가 죽으면 가만히 있음
		UCStateComponent* targetstate = CHelpers::GetComponent<UCStateComponent>(target);
		if (targetstate->IsDeadMode())
		{
			behavior->SetWaitMode();
			return;
		}
	}
	controller->SetFocus(target); //감지가 되면 플레이어를 쳐다봄
	

	float distance = aiPawn->GetDistanceTo(target); // 플레이어와 적 사이의 거리

	if (distance < controller->GetBehaviorRange())
	{
		behavior->SetAvoidMode();
		return;
	}
	if (distance < controller->GetSightRadius())
	{
		behavior->SetActionMode();
		return;
	}
	

}
