#include "Example.h"
#include "GameplayDebugger.h"
#include "LevelEditor.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "AssetToolsModule.h"
#include "01_DebugCategory/CGameplayDebugCategory.h"
#include "02_ToolbarCommand/CToolbarCommand.h"
#include "03_CustomDataAsset/CDataAssetToolAction.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);
	for (const FSlateBrush* brush : brushes)
		GLog->Log(brush->GetResourceName().ToString());

	UE_LOG(LogTemp,Error, L"START MODULE");

	//StyleSet
	{
		//��Ÿ�ϼ� ����
		StyleSet = MakeShareable(new FSlateStyleSet("ExampleStyle"));//Shared�����ͷ� ������� 

		//������ ���丮 ��Ʈ ����ֱ�
		FString path = IPluginManager::Get().FindPlugin("Example")->GetContentDir();//�÷������� Example�̶� �÷������� Content�������� �����
		StyleSet->SetContentRoot(path);

		//������ �� �������ֱ�
		FSlateImageBrush* brush = new FSlateImageBrush(path / L"Icon.png", FVector2D(48,48)); // /�� ��Ʈ�� �ΰ��� �̾��ش�
		StyleSet->Set("Example.ToolbarIcon", brush);

		//���� ���                 
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	}

	// DebugCategory
	{
		//�����÷��� ����� �̱��� ������
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); // Singletone ��ü ����

		//�츮�� ���� ī�װ��� ��ü �����ϱ�
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebugCategory::MakeInstance);

		//�츮�� ���� ī�װ��� ����ϱ�
		gameplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

	//ToolbarButton
	{
		//���� Ȯ�� ���
		CToolbarCommand::Register();
		ToolbarExtender = MakeShareable(new FExtender()); // new FExnteder;

		//���� ���ٿ� ��ư �߰�
		TSharedPtr<FUICommandList> commandList = MakeShareable(new FUICommandList());
		commandList->MapAction
		(
			CToolbarCommand::Get().Button,
			FExecuteAction::CreateRaw(this, &FExampleModule::ToolbarButton_Clicked),
			FCanExecuteAction()
		);
		Extension = ToolbarExtender->AddToolBarExtension
		(
			"Compile",
			EExtensionHook::After,
			commandList,
			FToolBarExtensionDelegate::CreateRaw(this, &FExampleModule::AddToolbarExtension)
		);

		//(1) ����Ȯ�� -> (2) Extension �г� ���� -> (3)���� �����Ϳ� �ٿ��ֱ�
		FLevelEditorModule& levelEditor =  FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);// ���� ���̰� ������

	}
	
	//Asset Tool
	{
		//������ ��� �Ŵ��� ��������
		IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		//ī�װ��� ����(��Ÿ ī�װ���)
		//EAssetTypeCategories::Type category = EAssetTypeCategories::Misc; //��Ÿ ī�װ���
		EAssetTypeCategories::Type category = assetTools.RegisterAdvancedAssetCategory(NAME_None,FText::FromString("Awesome Category")); //Ŀ���� ī�װ���


		//�ּ� �� �׼� ����
		Action = MakeShareable(new CDataAssetToolAction(category));

		//�ּ����� �׼� ���
		assetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}
	
	//Detail Panel
	{

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
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();

	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	ToolbarExtender.Reset();
	
}
void FExampleModule::AddToolbarExtension(class FToolBarBuilder& InBuilder)
{

	FSlateIcon icon = FSlateIcon("ExampleStyle","Example.ToolbarIcon");
	InBuilder.AddToolBarButton
	(
		CToolbarCommand::Get().Button,
		NAME_None,
		FText::FromString("YesJam"),
		FText::FromString("NoJam"),
		icon
	);
}

void FExampleModule::ToolbarButton_Clicked()
{
	UE_LOG(LogTemp, Error, L"Hello Hell World~~~");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)