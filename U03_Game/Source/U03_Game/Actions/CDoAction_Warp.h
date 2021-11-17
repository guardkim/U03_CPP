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
	virtual void Begin_DoAction() override; //��ƼŬ
	virtual void End_DoAction() override; // ĳ�����̵�

	virtual void Tick(float DeltaTime) override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator); // �����ϰ� ���콺��ġ�� �浹�ϸ� �ش��ϴ� ������ ��ġ������ ����
private:
	class UDecalComponent* Decal;
	FVector Location;
	
};
