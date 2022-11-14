// Don't touch my f*cking code!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMovementComponent.generated.h"

UENUM()
enum class EWalkingMode : uint8
{
	Walk,
	Jog,
	Run
};

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMainCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float TopWalkSpeed = 300.f;
	
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float TopJogSpeed = 600.f;
	
	UPROPERTY(Category="Character Movement: Running", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float TopRunSpeed = 1200.f;

	UFUNCTION(BlueprintCallable)
	void SetWalkingMode(EWalkingMode Mode);

	UFUNCTION(BlueprintCallable)
	EWalkingMode GetWalkingMode() const;

private:
	EWalkingMode WalkingMode = EWalkingMode::Walk;
};
