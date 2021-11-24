#include "CFeetComponent.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float leftDistance;
	Trace(LeftSocket,leftDistance);

	float rightDistance;
	Trace(RightSocket, rightDistance);

	float offset = FMath::Min(leftDistance, rightDistance);

	//Data.LeftDistance.X = leftDistance - offset; ���� �ڼ�ó�� ���� �ٴ´�(��������(lerp)�� ���� �־��� ����)
	//UKismetMathLibrary::RInterpTo(); //ȸ���� lerp
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X,(leftDistance - offset),DeltaTime, InterpSpeed); //vector�� vector������ lerp����
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X,-(leftDistance - offset),DeltaTime, InterpSpeed); //vector�� vector������ lerp����
	//AnimInstance�� �ѱ�
}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance)
{
	OutDistance = 0.0f;

	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z); 
	// z�� ĳ������ ��� ����(���̸�) x,y�� ���� ��ġ

	float traceZ = start.Z - CapsuleHalfHeight - TraceDistance; 
	FVector end = FVector(location.X, location.Y, traceZ); // �浹ü�κ���(���� �ִ� �������κ���) -55 �� ���������� end
	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);
	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), // ETraceTypeQuery
		true, //������ ��ܿ� Complex
		ignores,
		DrawDebugType,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	);
	//x,y�� ���� ��ġ��, z��ġ�� ĳ������ ��� ���̿������� �� �Ʒ� -55���� ���� �׷���

	CheckFalse(hitResult.IsValidBlockingHit()); //���ο� ������ �ƹ��͵����ٸ�

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size(); //������ ���� , �߹غ��� �Ʒ��� ���� �׷��� �浹���������� ������ ����
	OutDistance = OffsetDistance + length - TraceDistance; // OffsetDistance�� ������ ��, ������ �İ����� - ����� ����� ���� = ������ ���� ������� �� ����


}

