#include "CInteractDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACInteractDoor::ACInteractDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &Box, "Box", Scene);
	CHelpers::CreateComponent(this, &DoorFrame, "DoorFrame", Scene);
	CHelpers::CreateComponent(this, &Door, "Door", DoorFrame);

	UStaticMesh* doorFramemesh;
	CHelpers::GetAsset<UStaticMesh>(&doorFramemesh, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	DoorFrame->SetStaticMesh(doorFramemesh);

	UStaticMesh* doormesh;
	CHelpers::GetAsset<UStaticMesh>(&doormesh, "StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");
	Door->SetStaticMesh(doormesh);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->InitBoxExtent(FVector(150, 50, 100));
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetCollisionProfileName("Trigger"); // ���� Overlap




}

void ACInteractDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Box->SetHiddenInGame(bHiddenInGame);
}

void ACInteractDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bOpening) Opening(DeltaTime);
	if (bClosing) Closing(DeltaTime);
}

void ACInteractDoor::Interact(const FVector& InForward)
{
	float dot = InForward | Box->GetForwardVector(); //Dot Product ������ ^��, ����� ������ ��ġ, ������ ������ �ݴ�
	Direction = FMath::Sign(dot); //������ ������ -1�� �������, ����� ������ 1�θ�����ְ�, 90���� 0���� �������(�յ��Ǻ�)

	Degree = Direction * MaxDegree; //Ȱ¦ ������ �� ����( ������ �����)

	if (bClosed == true)
	{
		bClosed = false;
		bClosing = false; //Tick���� ��
		bOpening = true; //Tick���� �Ǵ��� ����
	}
	else
	{
		bClosed = true;
		bClosing = true; //Tick���� ��
		bOpening = false; //Tick���� �Ǵ��� ����
	}

}

void ACInteractDoor::Opening(float Delta)
{
	
}

void ACInteractDoor::Closing(float Delta)
{

}

