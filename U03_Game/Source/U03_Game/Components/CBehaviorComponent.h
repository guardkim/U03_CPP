#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"


UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Action, Patrol, Hitted, Avoid
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U03_GAME_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";
	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";
	UPROPERTY(EditAnywhere)
		FName WarpLocation = "WarpLocation";

public:
	UFUNCTION(BlueprintPure)
		bool IsWaitMode();
	UFUNCTION(BlueprintPure)
		bool IsApproachMode();
	UFUNCTION(BlueprintPure)
		bool IsActionMode();
	UFUNCTION(BlueprintPure)
		bool IsPatrolMode();
	UFUNCTION(BlueprintPure)
		bool IsHittedMode();
	UFUNCTION(BlueprintPure)
		bool IsAvoidMode();

	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();

	//블랙보드에서 읽어온 값 리턴
	class ACPlayer* GetTargetPlayer();
	FVector GetWarpLocation();
public:	
	UCBehaviorComponent();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(EBehaviorType InNewType); // 블랙보드의 키값을 세팅하는 용도
	EBehaviorType GetType(); // 현재 블랙보드에 쓰여져 있는 키값을 읽어오는 용도
public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	class UBlackboardComponent* Blackboard;

};
