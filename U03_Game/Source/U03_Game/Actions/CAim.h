#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAim.generated.h"

UCLASS()
class U03_GAME_API UCAim : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool IsAvaliable() { return SpringArm != nullptr && Camera != nullptr; } // SpringArm이 있고 Camera가 있으면 true
public:
	UCAim();
	void BeginPlay(class ACharacter* InCharacter);
	void Tick(float DeltaTime);

	void On();
	void Off();

private:
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bInZoom; //true면 줌을 주고 false면 줌인
};
