#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "CEnemy.generated.h"

UCLASS()
class U03_GAME_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

private: //Action, Montage, State, Status
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Actions;
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void ChangeColor(FLinearColor InColor) override;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

};