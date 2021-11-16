#include "CDoAction_Throw.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAim.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	// UPROPERTY를 넣지 않으면 61초 후에 널참조로 터진다. (가비지컬렉터 기본셋팅)
	Aim = NewObject<UCAim>();  // C++ 스타일 new할당 new 안됨 , shared_pointer로 Reference Counter가 0이 될 시 delete 하는 가비지 컬렉터를 사용함
	Aim->BeginPlay(OwnerCharacter);
}
void ACDoAction_Throw::DoAction()
{
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode(); //Idle
	Status->SetMove();  //bCanMove true
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Aim->Tick(DeltaTime);
}
void ACDoAction_Throw::OnAim()
{
	Aim->On();
}

void ACDoAction_Throw::OffAim()
{
	Aim->Off();
}

