#include "CPatrolComponent.h"
#include "Global.h"
#include "Objects/CPatrolPath.h"
#include "Components/SplineComponent.h"
UCPatrolComponent::UCPatrolComponent()
{
}

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius)
{
	//�ش� ���ö��� ����Ʈ �ε����� ���������� true �ƴϸ� false

	OutLocation = FVector::ZeroVector;
	OutAcceptanceRadius = AcceptanceRadius;
	
	CheckNullResult(Path, false); //PatrolComponent�� �־��ָ� ������θ� �������ټ� �ִµ�, ���°�� false�� ����
	
	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(index, ESplineCoordinateSpace::World);//Local�� ������ 0������ 1������ ������� �Ÿ��� ���´�
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	//bReverse�� true�� 3-2-1-0 , false�� 0-1-2-3
	CheckNull(Path);

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	//�������̶��
	if (bReverse)
	{
		if (index > 0)
		{
			index--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())//Loop�� �����ִٸ�
		{
			index = count - 1;
			return;
		}
		//Loop�� �ƴ϶��
		index = 1; //3-2-1-0 -> 0-1-2-3 �ݺ�
		bReverse = false;

		return;
	}
	//�������̶��

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
