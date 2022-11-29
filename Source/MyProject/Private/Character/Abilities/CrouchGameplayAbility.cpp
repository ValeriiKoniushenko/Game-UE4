// Don't touch my f*cking code!

#include "Character/Abilities/CrouchGameplayAbility.h"
#include "Character/MainCharacter.h"

void UCrouchGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

bool UCrouchGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags)
{
	AMainCharacter* Character = Cast<AMainCharacter>(ActorInfo->PlayerController->GetCharacter());
	check(Character);
	Character->PlayAnimMontage(Character->CrouchAnimMontage);
	
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

