#include "CUserWidget_Select.h"
#include "Global.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include "Widgets/CUserWidget_Selectitem.h"

void UCUserWidget_Select::NativeConstruct()
{
	TArray<UWidget*> children = Grid->GetAllChildren(); // Grid의 붙은 자식들 
	for (UWidget* child : children)
		Items.Add(child->GetName(), Cast<UCUserWidget_Selectitem>(child)); //Map에 저장됨


	Super::NativeConstruct();
}
void UCUserWidget_Select::Click(FString InName)
{
	if (Items[InName]->OnUserWidget_Select_Clicked.IsBound())
		Items[InName]->OnUserWidget_Select_Clicked.Broadcast();

	SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = false;
	UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}
void UCUserWidget_Select::Hover(FString InName)
{
	//Items.Find == Items[InName]
	//Border색깔 바꾸기
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("BG_Border"));//FName이라 대소문자 구분X
	if (!!border)
		border->SetBrushColor(FLinearColor::Red);
}

void UCUserWidget_Select::Unhover(FString InName)
{
	UBorder* border = Cast<UBorder>(Items[InName]->GetWidgetFromName("BG_Border"));
	if (!!border)
		border->SetBrushColor(FLinearColor::White);
}


