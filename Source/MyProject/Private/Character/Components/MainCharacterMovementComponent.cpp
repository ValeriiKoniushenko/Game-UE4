// Don't touch my f*cking code!


#include "Character/Components/MainCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogMovemementComponent, All, All);

void UMainCharacterMovementComponent::SetWalkingMode(EWalkingMode Mode)
{
	if (WalkingMode == EWalkingMode::Walk)
		LastMaxWalkSpeed = MaxWalkSpeed;
	
	WalkingMode = Mode;
	if (WalkingMode == EWalkingMode::SlowWalk)
		MaxWalkSpeed = MaxSlowWalkSpeed;
	else if (WalkingMode == EWalkingMode::Walk)
		MaxWalkSpeed = LastMaxWalkSpeed;
	else if (WalkingMode == EWalkingMode::Run)
		MaxWalkSpeed = MaxRunSpeed;
	else
		UE_LOG(LogMovemementComponent, Error, TEXT("Invalid walking mode"));
}

EWalkingMode UMainCharacterMovementComponent::GetWalkingMode() const
{
	return WalkingMode;
}
