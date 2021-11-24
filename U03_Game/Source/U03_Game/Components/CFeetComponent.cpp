#include "CFeetComponent.h"
#include "Global.h"
#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TriggerVolume.h"

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerVolume::StaticClass(), actors);
	for (AActor* actor : actors)
	{
		actor->OnActorBeginOverlap.AddDynamic(this, &UCFeetComponent::OnActorBeginOverlap);
		actor->OnActorEndOverlap.AddDynamic(this, &UCFeetComponent::OnActorEndOverlap);
	}
		//typeid(a) C��Ÿ�� Ŭ�������۷���
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float leftDistance;
	FRotator leftRotation;
	Trace(LeftSocket,leftDistance, leftRotation);

	float rightDistance;
	FRotator rightRotation;
	Trace(RightSocket, rightDistance, rightRotation);

	float offset = FMath::Min(leftDistance, rightDistance);

	//Data.LeftDistance.X = leftDistance - offset; ���� �ڼ�ó�� ���� �ٴ´�(��������(lerp)�� ���� �־��� ����)
	//UKismetMathLibrary::RInterpTo(); //ȸ���� lerp
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X,(leftDistance - offset),DeltaTime, InterpSpeed); //vector�� vector������ lerp����
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X,-(rightDistance - offset),DeltaTime, InterpSpeed); //vector�� vector������ lerp����
	Data.PevisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PevisDistance.Z, offset, DeltaTime, InterpSpeed); // Pelvis�� �׳� �����ָ��
	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
	//AnimInstance�� �ѱ�
	
}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
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

	//hitResult.ImpactNormal.Rotation();//Rollȸ���� ����

	FVector normal = hitResult.ImpactNormal;

	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z );//�浹�������ƴµ� ������ �𸦶�
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);

	OutRotation = FRotator(pitch, 0.0f, roll);

}

void UCFeetComponent::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CheckNull(Cast<ACharacter>(OtherActor));

	bIkMode = true;
}

void UCFeetComponent::OnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CheckNull(Cast<ACharacter>(OtherActor));
	bIkMode = false;
}

