#include "CAIController.h"
#include "Global.h"
#include "CEnemy_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");//�θ��� UBlackboardComponent

		
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset,Blackboard);
	//OwnerEnemy�� Blackboard�� ���ͼ�(AI_Melee�� �Ⱦ��� BehaviorTree�� Blackboard�� �Ⱦ���)
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}