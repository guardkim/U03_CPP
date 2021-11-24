#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CInteractDoor.generated.h"

UCLASS()
class U03_GAME_API ACInteractDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		float Speed = 80.0f;
	UPROPERTY(EditAnywhere)
		float MaxDegree = 90.0f;
	UPROPERTY(EditAnywhere)
		bool bHiddenInGame;

public:	
	ACInteractDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
