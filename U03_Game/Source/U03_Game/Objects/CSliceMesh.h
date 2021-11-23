#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSliceMesh.generated.h"

UCLASS()
class U03_GAME_API ACSliceMesh : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

public:
	//Static을 ProceduralMesh로 복사
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	ACSliceMesh();

	

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
