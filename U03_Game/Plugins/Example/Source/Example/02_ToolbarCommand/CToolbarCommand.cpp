#include "CToolbarCommand.h"

CToolbarCommand::CToolbarCommand()
	: TCommands
	(
		"NewButton",
		FText::FromString("NewButton"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	)
{

}

CToolbarCommand::~CToolbarCommand()
{
}
void CToolbarCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE "CToolbarCommand"
	UI_COMMAND //버튼을 만들기 위한 상세정보가 멤버변수 Button에 적용된다
	(
		Button,
		"FriendlyName",
		"Description",
		EUserInterfaceActionType::Button,
		FInputGesture()
	);

#undef LOCTEXT_NAMESPACE
}
