#include "CAim.h"
#include "Global.h"
#include "CHUD.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CStateComponent.h"

UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Actions/Curve_Aim.Curve_Aim'");
}
void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200.0f);

	//UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD<ACHUD>();//그냥 GetWorld()하면 안나옴
	Hud = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime); //이거 안넣어주면 타임라인 안돌아감 
}

void UCAim::On()
{
	CheckFalse(IsAvaliable());
	CheckTrue(bInZoom);

	bInZoom = true;

	Hud->SetDraw();

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10); //오른쪽 어깨쪽으로 카메라 옮겨줌
	SpringArm->bEnableCameraLag = false; // 카메라살짝 반박자 늦게 따라오는거

	Timeline.PlayFromStart();
	//Camera->FieldOfView = 45.0f; //시야각 FOV
}

void UCAim::Off()
{
	CheckFalse(IsAvaliable());
	CheckFalse(bInZoom);

	bInZoom = false;

	Hud->SetNoDraw();

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true; 

	Timeline.ReverseFromEnd();
	//Camera->FieldOfView = 90.0f;
}

void UCAim::Zooming(float Value)
{
	Camera->FieldOfView = Value;
}
