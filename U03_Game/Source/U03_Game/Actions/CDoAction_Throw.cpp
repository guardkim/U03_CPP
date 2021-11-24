#include "CDoAction_Throw.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "CAim.h"
#include "CThrow.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	// UPROPERTY를 넣지 않으면 61초 후에 널참조로 터진다. (가비지컬렉터 기본셋팅)
	Aim = NewObject<UCAim>();  // C++ 스타일 new할당 new 안됨 , shared_pointer로 Reference Counter가 0이 될 시 delete 하는 가비지 컬렉터를 사용함
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
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_ThrowItem");//월드 공간을 얻어온다
	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation(); //전방방향

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
	UProceduralMeshComponent* otherProcMesh = Cast<UProceduralMeshComponent>(InHitResult.GetComponent());

	if (!!otherProcMesh)
	{
		FVector planeNormals[2] = { GetActorUpVector(), GetActorRightVector() };
		UProceduralMeshComponent* outProcMesh = nullptr;

		UMaterialInstanceConstant* material;
		CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/MAT_Slice_Inst.MAT_Slice_Inst'");
		UKismetProceduralMeshLibrary::SliceProceduralMesh
		(
			otherProcMesh,	//자를 ProceduralMesh
			InHitResult.Location, //충돌된 지점에서 자르고 싶음
			planeNormals[UKismetMathLibrary::RandomIntegerInRange(0,1)], // 면이 향하는 방향, 지금은 업벡터나 라이트벡터 랜덤으로
			true, // 잘려져서 없앨건지 이등분할건지
			outProcMesh, // 잘린 면을 저장받을 변수
			EProcMeshSliceCapOption::CreateNewSectionForCap, // 잘린단면을 어떻게 할지, NoCap은 뻥 뚫림, CreateNewSectionForCap 새로운 면을 만들어줌, UseLastSectionForCap 단면을 복사해서 잘린 단면을 만들어줌
			material // 잘린 면의 색상을 바꿔주고싶을때(잘린단면을 표현하고싶을때)
		);
		outProcMesh->SetSimulatePhysics(true);
		outProcMesh->AddImpulse(FVector(1000.0f, 1000.0f, 1000.0f),NAME_None, true);
	}

	//누가 데미지를 받을 것인가
	FDamageEvent e;// 빗겨맞았는지... 스플래쉬 데미지인지
	InHitResult.GetActor()->TakeDamage(Datas[0].Power,e, OwnerCharacter->GetController(),this);//Magicball가져오기 애매해서 일단 Causer는 this...
	
}
void ACDoAction_Throw::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvaliable())
	CheckFalse(Aim->InZoom())
	Aim->Off();
	//CActionComponent의 ChangeType쪽의 함수를 딜리게이트에 바인딩 하는 형식으로 바꾼것
	//딜리게이트 바인딩은 BeginPlay에서
}

