// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SSInteractionHelper.generated.h"

class ISSInteraction;

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class SIMPLESHOOTER_API USSInteractionHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interaction(APawn* InOwner, AActor* InTargetActor);
	virtual void Interaction_Implementation(APawn* InOwner, AActor* InTargetActor) PURE_VIRTUAL(ThisClass::Interaction_Implementation, );
};
