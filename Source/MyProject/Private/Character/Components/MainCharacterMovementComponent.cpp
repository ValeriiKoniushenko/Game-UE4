// Don't touch my f*cking code!


#include "Character/Components/MainCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogMovemementComponent, All, All);

void UMainCharacterMovementComponent::SetWalkingMode(EWalkingMode Mode)
{
	WalkingMode = Mode;
	if (WalkingMode == EWalkingMode::Walk)
		MaxWalkSpeed = TopWalkSpeed;
	else if (WalkingMode == EWalkingMode::Jog)
		MaxWalkSpeed = TopJogSpeed;
	else if (WalkingMode == EWalkingMode::Run)
		MaxWalkSpeed = TopRunSpeed;
	else
		UE_LOG(LogMovemementComponent, Error, TEXT("Invalid walking mode"));
}

EWalkingMode UMainCharacterMovementComponent::GetWalkingMode() const
{
	return WalkingMode;
}
