// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SSInteractionHelperManager.h"

#include "Interaction/SSInteractionHelper.h"

void USSInteractionHelperManager::Interaction(APawn* InOwner, AActor* InTargetActor)
{
	for (const TObjectPtr<USSInteractionHelper>& Helper : Helpers)
	{
		if (!Helper)
		{
			continue;
		}

		Helper->Interaction(InOwner, InTargetActor);
	}
}
