#include "CDoAction_Tornado.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Characters/CEnemy.h"
#include "CAttachment.h"
#include "Particles/ParticleSystemComponent.h"

void ACDoAction_Tornado::BeginPlay()
{
	Super::BeginPlay();

	//Attachment::Box -> ��� Box ����
	for (AActor* actor : OwnerCharacter->Children) // ���� ���ʷ� ����ִ� ���͵�
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Tornado")) //actor�� ACAttachment�� ��ӹ޾Ҵ���, Attachment �ȿ� Tornado����
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor); // Tornado�ȿ� BoxCollision
			break;
		}
	}
}

void ACDoAction_Tornado::DoAction()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(bOnce); //�ߺ�����
	
	bOnce = true;
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,Datas[0].PlayRate,Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Tornado::Begin_DoAction()
{
	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, ""); //Box�� ���ϰŶ� Attached, 
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner()); //Attachment_Tornado�� Owner

	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ACDoAction_Tornado::End_DoAction()
{
	Status->SetMove();
	State->SetIdleMode();

	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer,DestroyTime,false);

	

}

void ACDoAction_Tornado::Abort()
{
	//�Ѵ������ ��� ��ҵǰ�
	Finish();
}

void ACDoAction_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = OwnerCharacter->GetActorLocation();
	
	Angle += Speed * DeltaTime;

	if (FMath::IsNearlyEqual(Angle, 360.0f)) //360���� ���������
		Angle = 0.0f;
	
	FVector rotVector = FVector(Distance, 0, 0); // �Ÿ���ŭ �÷��̾����׼� �����ְ�
	FVector yawVector = rotVector.RotateAngleAxis(Angle, FVector::UpVector); // Angle���� ���ư� ��(Yaw)
	
	location += yawVector;

	Box->SetWorldLocation(location);

}

void ACDoAction_Tornado::Hitted()
{
	FDamageEvent e;
	for (ACharacter* character : HittedCharacters)
	{
		bool bDead = false;
		//�´µ��� ������ null�� �ǵ帮�� ������ 
		ACEnemy* enemy = Cast<ACEnemy>(character);
		if (!!enemy)
		{
			UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(enemy);
			bDead = state->IsDeadMode();
			//���翩�ΰ� ������ ��, �����ֵ��� �����ϰ� TakeDamage
		}
		if (!!character && bDead == false)
		{
			character->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
			break;
		}
	}
}

void ACDoAction_Tornado::Finish()
{
	if (!!Attached)
		Attached->DestroyComponent();//ParticleComponent��
	
	bOnce = false;

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());

	attachment->OffCollision();

	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}

void ACDoAction_Tornado::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//�浹�Ǹ� ����
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}
