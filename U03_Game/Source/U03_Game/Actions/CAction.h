#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.generated.h"


USTRUCT(BlueprintType)
struct FEquipmentData // 디테일 패널
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;
	UPROPERTY(EditAnywhere)
		FName StartSection;
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.0f;
	UPROPERTY(EditAnywhere)
		float HitStop;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;
	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACThrow> ThrowClass;


};

UCLASS()
class U03_GAME_API UCAction : public UObject
{
	GENERATED_BODY()
	
public:
	friend class UCActionData; //frined 맺은 클래스끼리는 객체를 통해 private에 접근가능
public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }
private:
	class ACEquipment* Equipment;
	class ACAttachment* Attachment;
	class ACDoAction* DoAction;
	FLinearColor EquipmentColor;
};
