#include "Example.h"
#include "GameplayDebugger.h"
#include "LevelEditor.h"
#include "01_DebugCategory/CGameplayDebugCategory.h"
#include "02_ToolbarCommand/CToolbarCommand.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);
	for (const FSlateBrush* brush : brushes)
		GLog->Log(brush->GetResourceName().ToString());

	UE_LOG(LogTemp,Error, L"START MODULE");

	// DebugCategory
	{
		//게임플레이 디버거 싱글톤 얻어오기
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); // Singletone 객체 얻어옴

		//우리가 만든 카테고리 객체 생성하기
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebugCategory::MakeInstance);

		//우리가 만든 카테고리 등록하기
		gameplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

	//ToolbarButton
	{
		//툴바 확장 등록
		CToolbarCommand::Register();
		ToolbarExtender = MakeShareable(new FExtender()); // new FExnteder;

		//실제 툴바에 버튼 추가
		Extension = ToolbarExtender->AddToolBarExtension
		(
			"Compile",
			EExtensionHook::After,
			nullptr,
			FToolBarExtensionDelegate::CreateRaw(this, &FExampleModule::AddToolbarExtension)
		);

		//(1) 툴바확장 -> (2) Extension 패널 생성 -> (3)레벨 에디터에 붙여주기
		FLevelEditorModule& levelEditor =  FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);// 툴바 사이가 벌려짐

	}
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"SHUTDOWN MODULE");

	//디버거 객체가 살아있는지
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); // Singletone 객체 얻어옴

	// 해제
		gameplayDebugger.UnregisterCategory("ExampleCategory");
	}

	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	ToolbarExtender.Reset();
	
}
void FExampleModule::AddToolbarExtension(class FToolBarBuilder& InBuilder)
{

	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(),"LevelEditor.SelectMode");
	InBuilder.AddToolBarButton
	(
		CToolbarCommand::Get().Button,
		NAME_None,
		FText::FromString("YesJam"),
		FText::FromString("NoJam"),
		icon
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)