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
		float BehaviorRange = 150.0f;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;
public:
	ACAIController();

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
