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
	Box->SetCollisionProfileName("Trigger"); // 전부 Overlap




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
	float dot = InForward | Box->GetForwardVector(); //Dot Product 외적은 ^임, 양수면 방향이 일치, 음수면 방향이 반대
	Direction = FMath::Sign(dot); //음수면 무조건 -1로 만들어줌, 양수면 무조건 1로만들어주고, 90도면 0으로 만들어줌(앞뒤판별)

	Degree = Direction * MaxDegree; //활짝 열려야 될 각도( 방향이 고려된)

	if (bClosed == true)
	{
		bClosed = false;
		bClosing = false; //Tick에서 콜
		bOpening = true; //Tick에서 판단할 조건
	}
	else
	{
		bClosed = true;
		bClosing = true; //Tick에서 콜
		bOpening = false; //Tick에서 판단할 조건
	}

}

void ACInteractDoor::Opening(float Delta)
{
	
}

void ACInteractDoor::Closing(float Delta)
{

}

