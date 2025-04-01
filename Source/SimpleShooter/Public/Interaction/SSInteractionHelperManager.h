// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSInteractionHelperManager.generated.h"

class ISSInteraction;
class USSInteractionHelper;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class SIMPLESHOOTER_API USSInteractionHelperManager : public UObject
{
	GENERATED_BODY()

public:
	void Interaction(APawn* InOwner, AActor* InTargetActor);

protected:
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Interaction")
	TSet<TObjectPtr<USSInteractionHelper>> Helpers;
};
