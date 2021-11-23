#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Select.generated.h"



UCLASS()
class U03_GAME_API UCUserWidget_Select : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE class UCUserWidget_Selectitem* GetItem(FString InName) { return Items[InName]; }

public:
	void Click(FString InName);
	void Hover(FString InName);
	void Unhover(FString InName);

protected:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget)) // BindWidget을 붙여주면 위젯블프에 Grid타입을 넣어준다(없으면 null)
		class UGridPanel* Grid;
	UPROPERTY(BlueprintReadOnly)
		TMap<FString, class UCUserWidget_Selectitem*> Items;
};
