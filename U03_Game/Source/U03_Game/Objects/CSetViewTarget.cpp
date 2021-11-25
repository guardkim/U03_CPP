#include "CSetViewTarget.h"
#include "Global.h"
#include "Camera/CameraActor.h"

ACSetViewTarget::ACSetViewTarget()
{

}

void ACSetViewTarget::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	* 생각지도 못한 리플렉션 카메라가 하나 잡히기 때문에 이 코드로 카메라를 얻어오면 쓰기 힘들다
	* 블프에서 스포이드로 직접 배열에 인자를 잡아주자
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		ACameraActor* camera = Cast<ACameraActor>(actor);
		if (!!camera)
			Cameras.Add(camera);
	}*/

	UKismetSystemLibrary::K2_SetTimer(this, "Change", 2.0f, true); //함수 어디에있는지, 함수명, 몇초간, 무한반복


}

void ACSetViewTarget::Change()
{
	//카메라 매니저는 플레이어 컨트롤러에 있다, 쓸일이 많아서 UGameplayStatics에 있다
	//아래 코드는 카메라가 뚝뚝 끊기면서 바뀐다
	//APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//CheckNull(cameraManager);
	//CheckTrue(Cameras.Num() < 1); // 카메라 스포이드로 안넣어줫으면 
	//cameraManager->SetViewTarget(Cameras[Index]);
	//Index++;
	//Index %= Cameras.Num(); // 지정한 카메라 갯수 넘어가면(현재3개) 다시 0으로

	CheckFalse(bUseChangeCamera);
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	CheckTrue(Cameras.Num() < 1); // 카메라 스포이드로 안넣어줫으면 
	controller->SetViewTargetWithBlend(Cameras[Index], 2.0f,EViewTargetBlendFunction::VTBlend_Linear);

	Index++;
	Index %= Cameras.Num();
}
