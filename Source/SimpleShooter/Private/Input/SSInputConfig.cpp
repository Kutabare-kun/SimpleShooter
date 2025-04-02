// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SSInputConfig.h"

#include "SSLogCategory.h"

const UInputAction* USSInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FSSInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		SS_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."),
				*InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
