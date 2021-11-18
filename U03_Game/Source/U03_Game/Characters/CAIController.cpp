#include "CAIController.h"
#include "Global.h"
#include "CEnemy_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");//부모의 UBlackboardComponent

		
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
	//OwnerEnemy의 Blackboard를 얻어와서(AI_Melee의 꽂아준 BehaviorTree의 Blackboard를 꽂아줌)
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
