#include "CGameMode.h"
#include "Global.h"
#include "Characters/Cplayer.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"); // BP����� ����ϱ� ���� StaticClass��� ���

}

