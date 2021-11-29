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
	// return TSharedRef<IDetailCustomization>(); ��Ʈ�� ���� ����� ���Ҵ����� �α����� ������ ������ش�(������ ���� ����������)
	return MakeShareable(new CEditorDetailPanel);  //�α��� ������ ���ӵ� ��������(���Ҵ�) ������ش� 
}

void CEditorDetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Change Color");

	//Slate UI ����
	category.AddCustomRow(FText::FromString("Color"))
		.ValueContent()  //�������гο��� R-Value �ڸ���
		.VAlign(EVerticalAlignment::VAlign_Center) // ��� ����
		.MaxDesiredWidth(250) // �������� �г�
		[
			SNew(SButton).VAlign(EVerticalAlignment::VAlign_Center) // ���ο� ��ư ����
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