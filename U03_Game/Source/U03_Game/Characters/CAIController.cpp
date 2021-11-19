#include "CAIController.h"
#include "Global.h"
#include "CEnemy_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/CBehaviorComponent.h"
#include "Characters/CPlayer.h"

ACAIController::ACAIController()
{
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");//부모의 UBlackboardComponent
	CHelpers::CreateActorComponent(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent(this, &Perception, "Perception");
	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600.0f;
	Sight->LoseSightRadius = 800.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f;
	Sight->SetMaxAge(2.0f);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals= false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation()); //여러개의 SenseConfig를 
		
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset,Blackboard); // 어떤 블랙보드를 사용할지, BB_AI를 저장해줌
	//OwnerEnemy의 Blackboard를 얻어와서(AI_Melee의 꽂아준 BehaviorTree의 Blackboard를 꽂아줌) 변수에 저장

	SetGenericTeamId(OwnerEnemy->GetTeamID());
	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
	
	Behavior->SetBlackboard(Blackboard);
	//OwnerEnemy->GetBehaviorTree()->BlackboardAsset = 현재 사용중인 블랙보드(에너미)
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
	Perception->OnPerceptionUpdated.Clear(); //바인딩 된 함수 다 날리기
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACPlayer* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);

		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("Player", player); //Player키에다가 감지된 player를 넣어줌
}
