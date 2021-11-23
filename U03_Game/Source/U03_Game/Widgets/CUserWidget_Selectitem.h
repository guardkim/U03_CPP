#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Selectitem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUserWidget_Select_Clicked);

UCLASS()
class U03_GAME_API UCUserWidget_Selectitem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
		void Click();
	UFUNCTION(BlueprintCallable)
		void Hover(); //���콺 �÷�����
	UFUNCTION(BlueprintCallable)
		void Unhover();
public:
	UPROPERTY(BlueprintAssignable)
		FUserWidget_Select_Clicked OnUserWidget_Select_Clicked;
private:
	class UCUserWidget_Select* GetSelectWidget(); //���� ������ ��ü�� ������ ����(�Ҽ��� �θ� ����)
};
