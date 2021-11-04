#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontagesComponent.generated.h"


USTRUCT(BlueprintType)
struct FMontageData// include�Ϸ��� ��������� ������� �������ش�, �����Ҵ��� �ϴ� ���� �ƴϸ� ����ʿ��� ��Ŭ��� ������Ѵ�
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		FName StartSection;
	UPROPERTY(EditAnywhere)
		bool bCanMove;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U03_GAME_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

public:	
	UCMontagesComponent();

protected:
	virtual void BeginPlay() override;
	
private:
	TArray<FMontageData> MontageDatas;
};