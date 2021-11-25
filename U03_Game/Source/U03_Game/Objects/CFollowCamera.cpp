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
	FOnTimelineEvent finish; // FOnTimelineEventStatic을 상속받는
	finish.BindUFunction(this, "OnFinishProgress");

	Timeline = FTimeline(); // 모든 기본값을 쓰레기값이 안들어가게 잡아줌
	Timeline.AddInterpFloat(Spline->GetCurve(), progress); //커브 태워줌, 커브 태워서 뭐할건지
	Timeline.SetTimelineFinishedFunc(finish);
	Timeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);//타임라임 다 돌면 y값을 어떻게 할건지(마지막프레임값으로)
	Timeline.SetPlayRate(0.25f);//재생속도
	Timeline.PlayFromStart();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	CheckNull(controller);
	controller->SetViewTarget(this);
}

void ACFollowCamera::OnProgress(float Output)
{
	USplineComponent* spline = Spline->GetSpline();
	//CHelpers::GetComponent<USplineComponent>(Spline);
	float length = spline->GetSplineLength(); //spline 전체 길이

	FVector location = spline->GetLocationAtDistanceAlongSpline(Output * length,ESplineCoordinateSpace::World);//현재퍼센트*전체길이 = 카메라가 따라갈 위치
	FRotator rotation = spline->GetRotationAtDistanceAlongSpline(Output * length,ESplineCoordinateSpace::World);//현재퍼센트*전체길이 = 카메라가 따라갈 회전

	SetActorLocation(location);
	SetActorRotation(rotation);
}

void ACFollowCamera::OnFinishProgress()
{
	Timeline.Stop();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	controller->SetViewTarget(Cast<ACPlayer>(character));//Actor를 넣어주라고 되있지만 해당 Actor가 가지고 있는 카메라 컴포넌트로 바꿔줌
}

