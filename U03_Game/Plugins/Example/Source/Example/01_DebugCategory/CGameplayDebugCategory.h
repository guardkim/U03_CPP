#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"
#include "DebugRenderSceneProxy.h"

struct CGameplayDebugeCategory_Struct
{
	class AActor* Actor;
	FVector Location;
};

class EXAMPLE_API CGameplayDebugCategory : public FGameplayDebuggerCategory
{
public:
	CGameplayDebugCategory();
	~CGameplayDebugCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	//DebugActor의 데이터를 수집하는 함수, DebugActor = 카메라 시야에 들어온 Actor
	virtual void CollectData( APlayerController* OwnerPC,  AActor* DebugActor) override;
	//캔버스에 출력하는 용도
	virtual void DrawData( APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	CGameplayDebugeCategory_Struct Data;

};
