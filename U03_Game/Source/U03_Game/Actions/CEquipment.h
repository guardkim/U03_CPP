#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnEquipmentDelegate);

UCLASS()
class U03_GAME_API ACEquipment : public AActor
{
	GENERATED_BODY()
		 
public:
	FORCEINLINE void SetData(FEquipmentData InData) { Data = InData; }
	FORCEINLINE void SetColor(FLinearColor InColor) { Color = InColor; }
	FORCEINLINE const bool* GetEquipped() { return &bEquipped; }
	// bool* b = ACEquipment->GetEquipped();
	// *b = false; 이러면 ACEquipment의 bEquipped가 영향을 받지만 const로 읽기전용으로 만든다
	// 원래는 GetEquipped를 해야 값이 재적용 되지만 위의 주소참조 방식은 실시간으로 bEquipped의 변경내용이 적용된다
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
		FEquipmentDelegate	OnEquipmentDelegate;
	UPROPERTY(BlueprintAssignable)
		FUnEquipmentDelegate OnUnEquipmentDelegate;
public:	

	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void UnEquip();
	void UnEquip_Implementation();

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;
private:
	bool bEquipped;
	FEquipmentData Data;
	FLinearColor Color;

};
