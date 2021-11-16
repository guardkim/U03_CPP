#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class U03_GAME_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetDraw() { bDraw = true; }
	FORCEINLINE void SetNoDraw() { bDraw = false; }

private:
	//class UTexture
private:
	bool bDraw;

};
