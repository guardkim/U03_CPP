#include "CVertexActor.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertexActor::ACVertexActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent(this, &Mesh, "Mesh");

	float w = 50, h = 50, d = 50;

	//Quad Front
	Vertices.Add(FVector(-d, -w, -h)); //전방좌하
	Vertices.Add(FVector(-d, -w, +h)); //전방좌상
	Vertices.Add(FVector(-d, +w, -h)); //전방우하
	Vertices.Add(FVector(-d, +w, +h)); //전방우상
	AddRectangle(0);

	//Quad Back
	Vertices.Add(FVector(+d, -w, -h)); //후방좌하
	Vertices.Add(FVector(+d, +w, -h)); //후방우하
	Vertices.Add(FVector(+d, -w, +h)); //후방좌상
	Vertices.Add(FVector(+d, +w, +h)); //후방우상
	AddRectangle(4);

	//Quad Top
	Vertices.Add(FVector(-d, -w, +h)); //전방좌상
	Vertices.Add(FVector(+d, -w, +h)); //후방좌상
	Vertices.Add(FVector(-d, +w, +h)); //전방우상
	Vertices.Add(FVector(+d, +w, +h)); //후방우상
	AddRectangle(8);

	//Quad Bottom
	Vertices.Add(FVector(-d, -w, -h)); //전방좌하
	Vertices.Add(FVector(-d, +w, -h)); //전방우하
	Vertices.Add(FVector(+d, -w, -h)); //후방좌하
	Vertices.Add(FVector(+d, +w, -h)); //후방우하
	AddRectangle(12);

	//Quad Left
	Vertices.Add(FVector(+d, -w, -h)); //후방좌하
	Vertices.Add(FVector(+d, -w, +h)); //후방좌상
	Vertices.Add(FVector(-d, -w, -h)); //전방좌하
	Vertices.Add(FVector(-d, -w, +h)); //전방좌상
	AddRectangle(16);

	//Quad Right
	Vertices.Add(FVector(-d, +w, -h)); //전방우하
	Vertices.Add(FVector(-d, +w, +h)); //전방우상
	Vertices.Add(FVector(+d, +w, -h)); //후방우하
	Vertices.Add(FVector(+d, +w, +h)); //후방우상
	AddRectangle(20);



	//CreateMesh
	Mesh->CreateMeshSection
	(
		0, //Section Num
		Vertices,  //Vertices
		Indices, // Indices
		TArray<FVector>(), //Normal
		TArray<FVector2D>(), //UV
		TArray<FColor>(), //Color
		TArray<FProcMeshTangent>(), //Tangent
		true
	);
}

void ACVertexActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (int32 i = 0; i < Vertices.Num(); i++)
	{
		Vertices[i] += FVector(0, 0, Speed * DeltaTime);
	}
	Mesh->UpdateMeshSection
	(
		0, //Section No
		Vertices, // Vertices 
		TArray<FVector>(), // Normal
		TArray<FVector2D>(), // UV
		TArray<FColor>(), //Color
		TArray<FProcMeshTangent>() //Tangent
	);

}

void ACVertexActor::AddRectangle(int32 InStart)
{
	//2, 1, 0  3, 1, 2 -> 오른손좌표계
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);
	
	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);

}

