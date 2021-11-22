#include "CPatrolComponent.h"
#include "Global.h"
#include "Objects/CPatrolPath.h"
#include "Components/SplineComponent.h"
UCPatrolComponent::UCPatrolComponent()
{
}

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius)
{
	//해당 스플라인 포인트 인덱스로 갈수있으면 true 아니면 false

	OutLocation = FVector::ZeroVector;
	OutAcceptanceRadius = AcceptanceRadius;
	
	CheckNullResult(Path, false); //PatrolComponent를 넣어주면 순찰경로를 세팅해줄수 있는데, 없는경우 false를 리턴
	
	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(index, ESplineCoordinateSpace::World);//Local로 놓으면 0번에서 1번까지 상대적인 거리가 나온다
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	//bReverse가 true면 3-2-1-0 , false면 0-1-2-3
	CheckNull(Path);

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	//역주행이라면
	if (bReverse)
	{
		if (index > 0)
		{
			index--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())//Loop가 켜져있다면
		{
			index = count - 1;
			return;
		}
		//Loop가 아니라면
		index = 1; //3-2-1-0 -> 0-1-2-3 반복
		bReverse = false;

		return;
	}
	//정주행이라면

	if (index < count - 1)
	{
		index++;
		return;
	}
	if (Path->GetSpline()->IsClosedLoop())
	{
		index = 0;
		return;
	}

	index = count - 2;
	bReverse = true;
	return;
}


void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	
}
