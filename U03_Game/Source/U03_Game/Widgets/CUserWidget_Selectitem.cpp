#include "CUserWidget_Selectitem.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Widgets/CUserWidget_Select.h"

void UCUserWidget_Selectitem::Click() 
{
	GetSelectWidget()->Click(GetName());
}
void UCUserWidget_Selectitem::Hover()
{
	GetSelectWidget()->Hover(GetName());
}
void UCUserWidget_Selectitem::Unhover()
{
	GetSelectWidget()->Unhover(GetName());
}
UCUserWidget_Select* UCUserWidget_Selectitem::GetSelectWidget()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	return player->GetSelectWidget();
}