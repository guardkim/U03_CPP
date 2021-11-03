#include "CGameMode.h"
#include "Global.h"
#include "Characters/Cplayer.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"); // BP기능을 사용하기 위해 StaticClass대신 사용

}

