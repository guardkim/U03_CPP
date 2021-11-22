#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CPatrolComponent.h"
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
	UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(aiPawn);

	CheckTrue(state->IsDeadMode());


	if (state->IsHittedMode())//���� �°��ִٸ�
	{
		behavior->SetHittedMode();
		return;
	}
	ACPlayer* target = behavior->GetTargetPlayer();
	if (target == nullptr) // Ÿ���� ���ٸ�
	{
		if (patrol != nullptr && patrol->IsValid())
		{
			behavior->SetPatrolMode();
			return;
		}
		behavior->SetWaitMode();
		return;
	}

	float distance = aiPawn->GetDistanceTo(target); // ���� ���� �Ÿ�

	if (distance < controller->GetBehaviorRange()) // ���ݹ��� �ȿ� �ִٸ�	
	{
		behavior->SetActionMode();
		return;
	}

	if (distance < controller->GetSightRadius()) // �������� �ȿ� �÷��̾ �ִٸ�
	{
		behavior->SetApproachMode();
		return;
	}
}
