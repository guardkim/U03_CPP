#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

UCLASS()
class U03_GAME_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		bool bLoop;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene; //Transform �����뵵
	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }
public:	
	ACPatrolPath();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

};
