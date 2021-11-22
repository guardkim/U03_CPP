#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class U03_GAME_API ACAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.0f; //Melee는 공격범위 MagicBall은 도망갈 거리
	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true; // DrawDebugCircle을 그릴 것인지.
	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50.0f; //DrawDebugCircle이 그린 원이 땅에 뭍히지 않게 위로 올려줌
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

public:
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }
public:
	ACAIController();
	virtual void Tick(float DeltaTime) override;

	float GetSightRadius();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);//감지된 액터들이 배열로 들어옴

private:
	class ACEnemy_AI* OwnerEnemy;
	
	class UAISenseConfig_Sight* Sight;
};
