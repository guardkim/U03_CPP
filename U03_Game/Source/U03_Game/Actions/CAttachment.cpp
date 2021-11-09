#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent(this, &Scene, "Scene");
}

void ACAttachment::BeginPlay()
{
	// ���۵� ����
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	
	Super::BeginPlay();
}
void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

