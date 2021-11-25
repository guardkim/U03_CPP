#include "CFollowCamera.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "CCameraSpline.h"
#include "Characters/CPlayer.h"
ACFollowCamera::ACFollowCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Camera, "Camera");
}



void ACFollowCamera::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACCameraSpline::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		if (actor->IsA<ACCameraSpline>() && actor->GetName().Contains("BP_CCameraSpline"))
			Spline = Cast<ACCameraSpline>(actor);
	}
}

void ACFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
}

void ACFollowCamera::SetTimeline()
{
	FOnTimelineFloat progress;
	progress.BindUFunction(this, "OnProgress"); 
	FOnTimelineEvent finish; // FOnTimelineEventStatic�� ��ӹ޴�
	finish.BindUFunction(this, "OnFinishProgress");

	Timeline = FTimeline(); // ��� �⺻���� �����Ⱚ�� �ȵ��� �����
	Timeline.AddInterpFloat(Spline->GetCurve(), progress); //Ŀ�� �¿���, Ŀ�� �¿��� ���Ұ���
	Timeline.SetTimelineFinishedFunc(finish);
	Timeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);//Ÿ�Ӷ��� �� ���� y���� ��� �Ұ���(�����������Ӱ�����)
	Timeline.SetPlayRate(0.25f);//����ӵ�
	Timeline.PlayFromStart();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	CheckNull(controller);
	controller->SetViewTarget(this);
}

void ACFollowCamera::OnProgress(float Output)
{
	USplineComponent* spline = Spline->GetSpline();
	//CHelpers::GetComponent<USplineComponent>(Spline);
	float length = spline->GetSplineLength(); //spline ��ü ����

	FVector location = spline->GetLocationAtDistanceAlongSpline(Output * length,ESplineCoordinateSpace::World);//�����ۼ�Ʈ*��ü���� = ī�޶� ���� ��ġ
	FRotator rotation = spline->GetRotationAtDistanceAlongSpline(Output * length,ESplineCoordinateSpace::World);//�����ۼ�Ʈ*��ü���� = ī�޶� ���� ȸ��

	SetActorLocation(location);
	SetActorRotation(rotation);
}

void ACFollowCamera::OnFinishProgress()
{
	Timeline.Stop();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	controller->SetViewTarget(Cast<ACPlayer>(character));//Actor�� �־��ֶ�� �������� �ش� Actor�� ������ �ִ� ī�޶� ������Ʈ�� �ٲ���
}

