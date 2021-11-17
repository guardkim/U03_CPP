#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "Components/CActionComponent.h"
#include "CDoAction_Throw.generated.h"

UCLASS()
class U03_GAME_API ACDoAction_Throw : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	
public:
	FORCEINLINE class UCAim* GetAim() { return Aim; }

private:
	UFUNCTION()
		void AbortByTypeChanged(EActionType InPrevType, EActionType InNewType);
	//CActionComponent의 딜리게이트의 인자를 넣어줌으로써 딜리게이트에 바인딩 될 수 있는 조건을 만족함
	//인자들의 Enum때문에 헤더에 인클루드
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnAim() override;
	virtual void OffAim() override;

private:
	UFUNCTION()
		void OnThrowBeginOverlap(FHitResult InHitResult);
	UPROPERTY()
		class UCAim* Aim;
private:
	class UCActionComponent* Action;
};
