#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFeetComponent.generated.h"

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PevisDistance;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U03_GAME_API UCFeetComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName LeftSocket = "Foot_L";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName RightSocket = "Foot_R";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float TraceDistance = 55.0f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForOneFrame;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float OffsetDistance = 5.0f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		float InterpSpeed = 17.0f; // 발이 떨어지는 속도


public: 
	FORCEINLINE const FFeetData& GetData() { return Data; }
	FORCEINLINE bool GetIkMode() { return bIkMode; }
public:	
	UCFeetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Trace(FName InSocket, float& OutDistance, FRotator& OutRotation);

private:
	UFUNCTION()
		void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
private:
	FFeetData Data;

	class ACharacter* OwnerCharacter;
	float CapsuleHalfHeight;

	bool bIkMode;
		
};
