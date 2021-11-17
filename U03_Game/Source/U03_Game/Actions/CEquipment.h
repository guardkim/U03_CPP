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
	// *b = false; �̷��� ACEquipment�� bEquipped�� ������ ������ const�� �б��������� �����
	// ������ GetEquipped�� �ؾ� ���� ������ ������ ���� �ּ����� ����� �ǽð����� bEquipped�� ���泻���� ����ȴ�
	
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
