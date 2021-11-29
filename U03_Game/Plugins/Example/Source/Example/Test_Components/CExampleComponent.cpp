#include "CExampleComponent.h"

UCExampleComponent::UCExampleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCExampleComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCExampleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

