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
	* �������� ���� ���÷��� ī�޶� �ϳ� ������ ������ �� �ڵ�� ī�޶� ������ ���� �����
	* �������� �����̵�� ���� �迭�� ���ڸ� �������
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		ACameraActor* camera = Cast<ACameraActor>(actor);
		if (!!camera)
			Cameras.Add(camera);
	}*/

	UKismetSystemLibrary::K2_SetTimer(this, "Change", 2.0f, true); //�Լ� ����ִ���, �Լ���, ���ʰ�, ���ѹݺ�


}

void ACSetViewTarget::Change()
{
	//ī�޶� �Ŵ����� �÷��̾� ��Ʈ�ѷ��� �ִ�, ������ ���Ƽ� UGameplayStatics�� �ִ�
	//�Ʒ� �ڵ�� ī�޶� �Ҷ� ����鼭 �ٲ��
	//APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//CheckNull(cameraManager);
	//CheckTrue(Cameras.Num() < 1); // ī�޶� �����̵�� �ȳ־�Z���� 
	//cameraManager->SetViewTarget(Cameras[Index]);
	//Index++;
	//Index %= Cameras.Num(); // ������ ī�޶� ���� �Ѿ��(����3��) �ٽ� 0����

	CheckFalse(bUseChangeCamera);
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	CheckTrue(Cameras.Num() < 1); // ī�޶� �����̵�� �ȳ־�Z���� 
	controller->SetViewTargetWithBlend(Cameras[Index], 2.0f,EViewTargetBlendFunction::VTBlend_Linear);

	Index++;
	Index %= Cameras.Num();
}
