#include "CGameMode.h"
#include "Global.h"
#include "CHUD.h"
#include "Characters/Cplayer.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"); 
	// BP����� ����ϱ� ���� StaticClass��� ���
	CHelpers::GetClass<AHUD>(&HUDClass, "Blueprint'/Game/BP_CHUD.BP_CHUD_C'");
}

