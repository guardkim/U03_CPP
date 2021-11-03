#include "CStatusComponent.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{
}

void UCStatusComponent::SetMove()
{
	bCanMove = true;
}

void UCStatusComponent::SetStop()
{
	bCanMove = false;
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	
}
