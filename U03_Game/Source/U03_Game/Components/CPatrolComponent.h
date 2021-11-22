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
	//Spline Point의 Index를 저장할 변수
	UPROPERTY(EditAnywhere)
		int32 index;
	//정방향 역방향
	UPROPERTY(EditAnywhere)
		bool bReserve; 
	//Spline Point의 주변의 반경
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 50.0f;

public:
	// Path가 있을때만
 	FORCEINLINE bool ISValid() { return Path != nullptr; }
public:	
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

};
