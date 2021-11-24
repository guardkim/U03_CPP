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
		//typeid(a) C스타일 클래스레퍼런스
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

	//Data.LeftDistance.X = leftDistance - offset; 발이 자석처럼 착착 붙는다(선형보간(lerp)을 통해 넣어줄 예정)
	//UKismetMathLibrary::RInterpTo(); //회전용 lerp
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X,(leftDistance - offset),DeltaTime, InterpSpeed); //vector와 vector끼리의 lerp전용
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X,-(rightDistance - offset),DeltaTime, InterpSpeed); //vector와 vector끼리의 lerp전용
	Data.PevisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PevisDistance.Z, offset, DeltaTime, InterpSpeed); // Pelvis는 그냥 내려주면됨
	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
	//AnimInstance로 넘김
	
}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.0f;

	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z); 
	// z는 캐릭터의 가운데 높이(높이만) x,y는 발의 위치

	float traceZ = start.Z - CapsuleHalfHeight - TraceDistance; 
	FVector end = FVector(location.X, location.Y, traceZ); // 충돌체로부터(발이 있는 지점으로부터) -55 더 내려간곳이 end
	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);
	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), // ETraceTypeQuery
		true, //나선형 계단에 Complex
		ignores,
		DrawDebugType,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	);
	//x,y는 발의 위치고, z위치는 캐릭터의 가운데 높이에서부터 발 아래 -55까지 선을 그려줌

	CheckFalse(hitResult.IsValidBlockingHit()); //라인에 닿은게 아무것도없다면


	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size(); //벡터의 길이 , 발밑부터 아래로 선이 그려진 충돌지점까지의 벡터의 길이
	OutDistance = OffsetDistance + length - TraceDistance; // OffsetDistance는 보정용 값, 실제로 파고든길이 - 검출용 가상용 길이 = 실제로 발을 끌어내려야 할 높이

	//hitResult.ImpactNormal.Rotation();//Roll회전이 없다

	FVector normal = hitResult.ImpactNormal;

	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z );//충돌방향은아는데 각도를 모를때
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

