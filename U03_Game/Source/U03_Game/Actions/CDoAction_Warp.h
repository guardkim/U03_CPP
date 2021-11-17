#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class U03_GAME_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void DoAction() override; 
	virtual void Begin_DoAction() override; //파티클
	virtual void End_DoAction() override; // 캐릭터이동

	virtual void Tick(float DeltaTime) override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator); // 지면하고 마우스위치가 충돌하면 해당하는 지점의 위치정보를 리턴
private:
	class UDecalComponent* Decal;
	FVector Location;
	
};
