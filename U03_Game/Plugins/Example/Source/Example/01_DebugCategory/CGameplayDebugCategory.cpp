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
	return MakeShareable(new CGameplayDebugCategory()); //Shared ref ������ִ� �Լ�
}
void CGameplayDebugCategory::CollectData(class APlayerController* OwnerPC, class AActor* DebugActor)
{

	if (!!DebugActor)
	{
		Data.Actor = DebugActor;
		Data.Location = DebugActor->GetActorLocation();
	}
}
void CGameplayDebugCategory::DrawData(class APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (!!Data.Actor)
	{
		//DebugActor�� �̸����
		CanvasContext.Printf(FColor(255, 0, 0), L"Name : %s", *Data.Actor->GetName());// String�տ� *����ָ� char * Ÿ������ �ٲ��
		//DebugActor�� ���� ��ġ�� ����
		CanvasContext.Printf(FColor(0, 255, 0), L"Location : %s", *Data.Location.ToString());
		//DebugActor�� �÷��̾������ �Ÿ��� ����
		CanvasContext.Printf(FColor(0, 0, 255), L"Distance : %f", OwnerPC->GetPawn()->GetDistanceTo(Data.Actor));
	}
}
