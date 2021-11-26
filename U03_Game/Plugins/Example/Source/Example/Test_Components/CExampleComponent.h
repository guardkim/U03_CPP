#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CExampleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXAMPLE_API UCExampleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCExampleComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
