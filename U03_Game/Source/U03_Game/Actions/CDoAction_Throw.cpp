#include "CDoAction_Throw.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAim.h"
#include "CThrow.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	// UPROPERTY�� ���� ������ 61�� �Ŀ� �������� ������. (�������÷��� �⺻����)
	Aim = NewObject<UCAim>();  // C++ ��Ÿ�� new�Ҵ� new �ȵ� , shared_pointer�� Reference Counter�� 0�� �� �� delete �ϴ� ������ �÷��͸� �����
	Aim->BeginPlay(OwnerCharacter);

	Action = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	Action->OnActionTypeChanged.AddDynamic(this, &ACDoAction_Throw::AbortByTypeChanged);
}
void ACDoAction_Throw::DoAction()
{
	if (Aim->IsAvaliable())
		CheckFalse(Aim->InZoom());
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_ThrowItem");//���� ������ ���´�
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation(); //�������

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotator));

	ACThrow* throwObject = GetWorld()->SpawnActorDeferred<ACThrow>(Datas[0].ThrowClass, transform, OwnerCharacter, nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	throwObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(throwObject, transform);
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

void ACDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{
	//���� �������� ���� ���ΰ�
	FDamageEvent e;// ���ܸ¾Ҵ���... ���÷��� ����������
	InHitResult.GetActor()->TakeDamage(Datas[0].Power,e, OwnerCharacter->GetController(),this);//Magicball�������� �ָ��ؼ� �ϴ� Causer�� this...
	
}
void ACDoAction_Throw::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvaliable())
	CheckFalse(Aim->InZoom())
	Aim->Off();
	//CActionComponent�� ChangeType���� �Լ��� ��������Ʈ�� ���ε� �ϴ� �������� �ٲ۰�
	//��������Ʈ ���ε��� BeginPlay����
}
