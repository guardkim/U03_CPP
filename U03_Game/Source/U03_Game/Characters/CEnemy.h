#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class U03_GAME_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

		


private:
	UPROPERTY(EditAnywhere, Category = "DebugSettings")
		bool bDrawName = true;//위젯을 그리거나 끄거나
	UPROPERTY(EditDefaultsOnly)
		float LaunchValue = 100.0f;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;
protected: //Action, Montage, State, Status // 블프에서 사용하려면 protected
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly) //블프에서 사용하려면 ReadOnly or ReadWrite
		class UCActionComponent* Action;
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;
public:
	ACEnemy();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	//Pawn.h의 TakeDamage를 재정의 해주면 데미지를 받는쪽이 된다.

protected:
	virtual void BeginPlay() override;

public:
	virtual void ChangeColor(FLinearColor InColor) override;
	

	UFUNCTION()
		void ResetColor();
private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Hitted();
	void Dead();
	void End_Dead() override;
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

private:
	class AController* DamageInstigator;
};
