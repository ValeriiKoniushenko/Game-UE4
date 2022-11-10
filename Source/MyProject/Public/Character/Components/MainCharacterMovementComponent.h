// Don't touch my f*cking code!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMainCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0", ClampMax="100", UIMax="100"))
	float RunSpeedMultiplier = 1.5f;
};
