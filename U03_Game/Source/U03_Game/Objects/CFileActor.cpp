#include "CFileActor.h"
#include "Global.h"
#include "Serialization/BufferArchive.h"

ACFileActor::ACFileActor()
{
	CHelpers::CreateActorComponent(this, &InputComponent, "InputComponent");
}

void ACFileActor::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	EnableInput(controller);

	InputComponent->BindAction("FileSave", EInputEvent::IE_Pressed, this, &ACFileActor::OnSave);
	InputComponent->BindAction("FileLoad", EInputEvent::IE_Pressed, this, &ACFileActor::OnLoad);
}

void ACFileActor::OnSave()
{
	FFileData data;
	data.Name = "rlarudgh";
	data.Health = 99.9f;
	
	FBufferArchive buffer;//stream의 역할을 해준다
	//buffer << data.Name;
	//buffer << data.Health;
	buffer << data;

	CheckTrue(buffer.Num() < 1);
	buffer.FlushCache(); // 디스크로 몰아넣어줌 버퍼는 비고 하드에 저장됨
	FString str = FPaths::ProjectDir() + FString("Test.bin"); //우리 프로젝트의 디렉토리
	bool b = FFileHelper::SaveArrayToFile(buffer, *str); 
	buffer.Empty();
	CLog::Print(b ? "Saved" : "Failed");
}

void ACFileActor::OnLoad()
{
	FString str = FPaths::ProjectDir() + FString("Test.bin");

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *str);

	FMemoryReader reader = FMemoryReader(buffer, true);
	reader.Seek(0);

	FFileData data;
	//reader << data.Name;//저장했던 순서 그대로
	//reader << data.Health;
	reader << data;

	CLog::Print(data.Name.ToString(), -1, 10.0f, FColor::Red);
	CLog::Print(data.Health, -1, 10.0f, FColor::Red);
	
	reader.FlushCache();
	reader.Close();

}
