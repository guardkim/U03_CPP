#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
ACHUD::ACHUD()
{
	CHelpers::GetAsset<UTexture2D>(&Texture, "Texture2D'/Game/Textures/Widget/T_Crosshair.T_Crosshair'");
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();
	CheckFalse(bDraw);
	CheckNull(Texture);

	FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f); // 화면 안쪽에 들어오는 것의 절반, 화면해상도의 절반, 전체화면의 중점이나옴
	FVector2D size(Texture->GetSurfaceWidth() * 0.5f, Texture->GetSurfaceHeight() * 0.5f);
	FVector2D position = center - size;

	FCanvasTileItem item(position, Texture->Resource, FLinearColor::White);
	item.BlendMode = SE_BLEND_Translucent; 
	//Src.rgb * srcBlend (op) Dest.rgb * DestBlend

	Canvas->DrawItem(item);
}
