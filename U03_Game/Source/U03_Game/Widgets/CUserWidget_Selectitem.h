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
		void Hover(); //마우스 올렸을때
	UFUNCTION(BlueprintCallable)
		void Unhover();
public:
	UPROPERTY(BlueprintAssignable)
		FUserWidget_Select_Clicked OnUserWidget_Select_Clicked;
private:
	class UCUserWidget_Select* GetSelectWidget(); //나를 포함한 전체의 아이템 리턴(소속한 부모를 리턴)
};
