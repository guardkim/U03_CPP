#include "CDoAction_Warp.h"
#include "Global.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Components/CBehaviorComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Characters/CPlayer.h"
#include "CAttachment.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();
	
	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = CHelpers::GetComponent<UDecalComponent>(actor);
			break;
		}
	}
}
void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	CheckFalse(*bEquipped);

	if (UseCursorLocation())
	{
		FRotator rotator;
		CheckFalse(GetCursorLocationAndRotation(Location, rotator));
	}
	else
	{
		AAIController* controller = OwnerCharacter->GetController<AAIController>();
		UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

		Location = behavior->GetWarpLocation();
		Decal->SetVisibility(false);
	}
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}
void ACDoAction_Warp::Begin_DoAction()
{
	FTransform transform = Datas[0].EffectTransform;
	UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, OwnerCharacter->GetMesh(), "",transform.GetLocation(),FRotator(transform.GetRotation()),transform.GetScale3D());
}

void ACDoAction_Warp::End_DoAction()
{
	OwnerCharacter->SetActorLocation(Location);
	Location = FVector::ZeroVector;
	State->SetIdleMode();
	Status->SetMove();
}
void ACDoAction_Warp::Tick(float DeltaTime)
{
	CheckFalse(*bEquipped); // Equipment의 bEquipped를 DoAction 부모클래스에서 얻어와서 Warp에서 체크함

	if (UseCursorLocation() == nullptr)
	{
		Decal->SetVisibility(false);
		return;
	}
	FVector location;
	FRotator rotator;
	if (GetCursorLocationAndRotation(location, rotator))
	{
		Decal->SetVisibility(true);
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotator);
	}
	else
		Decal->SetVisibility(false);
}

ACPlayer* ACDoAction_Warp::UseCursorLocation()
{

	return Cast<ACPlayer>(OwnerCharacter); // 플레이어면 주소가 리턴되고 AI면 false가 리턴된다
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotator = hitResult.ImpactNormal.Rotation();
		return true;
	}
	return false;
}
