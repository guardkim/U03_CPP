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

	//DebugActor�� �����͸� �����ϴ� �Լ�, DebugActor = ī�޶� �þ߿� ���� Actor
	virtual void CollectData( APlayerController* OwnerPC,  AActor* DebugActor) override;
	//ĵ������ ����ϴ� �뵵
	virtual void DrawData( APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

private:
	CGameplayDebugeCategory_Struct Data;

};
