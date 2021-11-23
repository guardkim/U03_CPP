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

	//Attachment::Box -> 멤버 Box 저장
	for (AActor* actor : OwnerCharacter->Children) // 나를 오너로 삼고있는 액터들
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Tornado")) //actor가 ACAttachment를 상속받았는지, Attachment 안에 Tornado인지
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor); // Tornado안에 BoxCollision
			break;
		}
	}
}

void ACDoAction_Tornado::DoAction()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(bOnce); //중복방지
	
	bOnce = true;
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,Datas[0].PlayRate,Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Tornado::Begin_DoAction()
{
	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, ""); //Box에 붙일거라서 Attached, 
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner()); //Attachment_Tornado가 Owner

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
	//한대맞으면 모두 취소되게
	Finish();
}

void ACDoAction_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = OwnerCharacter->GetActorLocation();
	
	Angle += Speed * DeltaTime;

	if (FMath::IsNearlyEqual(Angle, 360.0f)) //360도에 가까워지면
		Angle = 0.0f;
	
	FVector rotVector = FVector(Distance, 0, 0); // 거리만큼 플레이어한테서 벌려주고
	FVector yawVector = rotVector.RotateAngleAxis(Angle, FVector::UpVector); // Angle값과 돌아갈 축(Yaw)
	
	location += yawVector;

	Box->SetWorldLocation(location);

}

void ACDoAction_Tornado::Hitted()
{
	FDamageEvent e;
	for (ACharacter* character : HittedCharacters)
	{
		bool bDead = false;
		//맞는도중 죽으면 null을 건드리기 때문에 
		ACEnemy* enemy = Cast<ACEnemy>(character);
		if (!!enemy)
		{
			UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(enemy);
			bDead = state->IsDeadMode();
			//생사여부가 저장이 됨, 죽은애들은 제외하고 TakeDamage
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
		Attached->DestroyComponent();//ParticleComponent라서
	
	bOnce = false;

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());

	attachment->OffCollision();

	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}

void ACDoAction_Tornado::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//충돌되면 들어옴
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}
