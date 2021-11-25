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

