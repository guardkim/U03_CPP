#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U03_GAME_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class ACPatrolPath* Path;
	//Spline Point�� Index�� ������ ����
	UPROPERTY(EditAnywhere)
		int32 index;
	//������ ������
	UPROPERTY(EditAnywhere)
		bool bReserve; 
	//Spline Point�� �ֺ��� �ݰ�
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 50.0f;

public:
	// Path�� ��������
 	FORCEINLINE bool ISValid() { return Path != nullptr; }
public:	
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

};
