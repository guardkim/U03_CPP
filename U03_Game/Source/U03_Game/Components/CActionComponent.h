#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, Warp, Tornado, MagicBall, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U03_GAME_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class UCActionData* DatasAssets[(int32)EActionType::Max];
	// 사용자가 값을 넣어줌

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE class UCAction* GetCurrent() { return Datas[(int32)Type]; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isUnarmedMode() { return Type == EActionType::Unarmed; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isFistMode() { return Type == EActionType::Fist; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isOneHandMode() { return Type == EActionType::OneHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isTwoHandMode() { return Type == EActionType::TwoHand; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isWarpMode() { return Type == EActionType::Warp; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isTornadoMode() { return Type == EActionType::Tornado; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool isMagicBallMode() { return Type == EActionType::MagicBall; }



public:
	UCActionComponent();

	
	UFUNCTION(BlueprintCallable) void SetUnarmedMode();
	UFUNCTION(BlueprintCallable) void SetFistMode();
	UFUNCTION(BlueprintCallable) void SetOneHandMode();
	UFUNCTION(BlueprintCallable) void SetTwoHandMode();
	UFUNCTION(BlueprintCallable) void SetWarpMode();
	UFUNCTION(BlueprintCallable) void SetTornadoMode();
	UFUNCTION(BlueprintCallable) void SetMagicBallMode();

	void OffAllCollision();

public:
	void DoAction();

	void DoOnAim();
	void DoOffAim();

	void Dead(); //무기의 충돌체 다 꺼버린다
	void End_Dead();
	void AbortByDamaged();
private:
	void SetMode(EActionType InType);
	void ChangeType(EActionType InNewType);
protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChanged OnActionTypeChanged;
private:
	EActionType Type;
	UPROPERTY()
		class UCAction* Datas[(int32)EActionType::Max];
	//CAction에 저장받기 위함 SpawnDeffed된 결과를 저장, 가비지컬렉터 주의(UPROPERTY)
};
