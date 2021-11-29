#include "CEditorDetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"	
#include "Widgets/Input/SButton.h"
#include "Objects/CButtonActor.h"

CEditorDetailPanel::CEditorDetailPanel()
{
}

CEditorDetailPanel::~CEditorDetailPanel()
{
}


TSharedRef<IDetailCustomization> CEditorDetailPanel::MakeInstance()
{
	// return TSharedRef<IDetailCustomization>(); 컨트롤 블럭을 만든다 힙할당으로 두군데의 공간에 만들어준다(공간이 따로 떨어져있음)
	return MakeShareable(new CEditorDetailPanel);  //두군데 공간을 연속된 공간으로(힙할당) 만들어준다 
}

void CEditorDetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Change Color");

	//Slate UI 문법
	category.AddCustomRow(FText::FromString("Color"))
		.ValueContent()  //디테일패널에서 R-Value 자리로
		.VAlign(EVerticalAlignment::VAlign_Center) // 가운데 정렬
		.MaxDesiredWidth(250) // 오버레이 패널
		[
			SNew(SButton).VAlign(EVerticalAlignment::VAlign_Center) // 내부에 버튼 만듬
			.OnClicked(this, &CEditorDetailPanel::OnClicked)
			.Content()
			[
				SNew(STextBlock).Text(FText::FromString("RandomColor"))
			]
		];
	
	DetailBuilder.GetObjectsBeingCustomized(Objects);

}

FReply CEditorDetailPanel::OnClicked()
{
	for (TWeakObjectPtr<UObject>& object : Objects)
	{
		GLog->Log(object->GetName());
	}
	return FReply::Handled();
}