// Don't touch my f*cking code!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMovementComponent.generated.h"

UENUM()
enum class EWalkingMode : uint8
{
	SlowWalk,
	Walk,
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
	UPROPERTY(Category="Character Movement: Slow Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float MaxSlowWalkSpeed = 300.f;
	
	UPROPERTY(Category="Character Movement: Running", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float MaxRunSpeed = 1200.f;

	UFUNCTION(BlueprintCallable)
	void SetWalkingMode(EWalkingMode Mode);

	UFUNCTION(BlueprintCallable)
	EWalkingMode GetWalkingMode() const;

private:
	EWalkingMode WalkingMode = EWalkingMode::Walk;
	float LastMaxWalkSpeed = MaxWalkSpeed;
};
