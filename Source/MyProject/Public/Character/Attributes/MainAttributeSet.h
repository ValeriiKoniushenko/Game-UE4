// Don't touch my f*cking code!

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MainAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSOR(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MYPROJECT_API UMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData DamageEffect = 10.f;
	ATTRIBUTE_ACCESSOR(UMainAttributeSet, DamageEffect);
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health = 100.f;
	ATTRIBUTE_ACCESSOR(UMainAttributeSet, Health);
};

#undef ATTRIBUTE_ACCESSOR