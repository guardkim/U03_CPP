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
		controller->ClearFocus(EAIFocusPriority::Gameplay); //���� ��� �Ĵٺ��� �ʰ� �ѹ� ������
		return;
	}
	else
	{
		//�÷��̾ ������ ������ ����
		UCStateComponent* targetstate = CHelpers::GetComponent<UCStateComponent>(target);
		if (targetstate->IsDeadMode())
		{
			behavior->SetWaitMode();
			return;
		}
	}
	controller->SetFocus(target); //������ �Ǹ� �÷��̾ �Ĵٺ�
	

	float distance = aiPawn->GetDistanceTo(target); // �÷��̾�� �� ������ �Ÿ�

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
