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
		//�����÷��� ����� �̱��� ������
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); // Singletone ��ü ����

		//�츮�� ���� ī�װ� ��ü �����ϱ�
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebugCategory::MakeInstance);

		//�츮�� ���� ī�װ� ����ϱ�
		gameplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

	//ToolbarButton
	{
		//���� Ȯ�� ���
		CToolbarCommand::Register();
		ToolbarExtender = MakeShareable(new FExtender()); // new FExnteder;

		//���� ���ٿ� ��ư �߰�
		Extension = ToolbarExtender->AddToolBarExtension
		(
			"Compile",
			EExtensionHook::After,
			nullptr,
			FToolBarExtensionDelegate::CreateRaw(this, &FExampleModule::AddToolbarExtension)
		);

		//(1) ����Ȯ�� -> (2) Extension �г� ���� -> (3)���� �����Ϳ� �ٿ��ֱ�
		FLevelEditorModule& levelEditor =  FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);// ���� ���̰� ������

	}
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"SHUTDOWN MODULE");

	//����� ��ü�� ����ִ���
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); // Singletone ��ü ����

	// ����
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