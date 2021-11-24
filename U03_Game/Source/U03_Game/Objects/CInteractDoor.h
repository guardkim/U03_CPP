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
		bool bHiddenInGame = true;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;

public:	
	ACInteractDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact(const FVector& InForward);//캐릭터나 카메라의 전방벡터를 인자로 받는다

private:
	void Opening(float Delta);
	void Closing(float Delta);

private:
	bool bClosed = true;
	bool bOpening = false;
	bool bClosing = false;

	float Direction; //문이 열릴 방향
	float Degree; //점점열리고있는 현재 각도

	float AddRotation; //누적되는 회전값

};
