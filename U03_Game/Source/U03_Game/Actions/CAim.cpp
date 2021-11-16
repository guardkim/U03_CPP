#include "CAim.h"
#include "Global.h"
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
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime); //�̰� �ȳ־��ָ� Ÿ�Ӷ��� �ȵ��ư� 
}

void UCAim::On()
{
	CheckFalse(IsAvaliable());
	CheckTrue(bInZoom);

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10); //������ ��������� ī�޶� �Ű���
	SpringArm->bEnableCameraLag = false; // ī�޶��¦ �ݹ��� �ʰ� ������°�

	Timeline.PlayFromStart();
	//Camera->FieldOfView = 45.0f; //�þ߰� FOV
}

void UCAim::Off()
{
	CheckFalse(IsAvaliable());
	CheckFalse(bInZoom);

	bInZoom = false;

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
