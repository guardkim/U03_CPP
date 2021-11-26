#include "CGameplayDebugCategory.h"

CGameplayDebugCategory::CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory Start");
}

CGameplayDebugCategory::~CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory End");

}

TSharedRef<FGameplayDebuggerCategory> CGameplayDebugCategory::MakeInstance()
{
	return MakeShareable(new FGameplayDebuggerCategory()); //Shared ref 만들어주는 함수
}
