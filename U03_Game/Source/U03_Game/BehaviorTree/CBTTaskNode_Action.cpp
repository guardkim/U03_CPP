#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

	bNotifyTick = true; // 이게 있어야 아래 TickTask가 동작
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());

	UCActionComponent* action = CHelpers::GetComponent<UCActionComponent>(aiPawn);

	TotalTime = 0.0f;
	action->DoAction();

	return EBTNodeResult::InProgress; //InProgress로 리턴하면 틱으로 넘어간다
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	TotalTime += DeltaSeconds;

	if (state->IsIdleMode() && TotalTime > Delay) //아이들 상태이고, TotalTime > Delay
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // 리턴타입이 void라서 이 함수를 써준다
}
