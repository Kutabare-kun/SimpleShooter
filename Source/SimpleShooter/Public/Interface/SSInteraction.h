// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USSInteraction : public UInterface
{
	GENERATED_BODY()
};

class SIMPLESHOOTER_API ISSInteraction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(APawn* InstigatorPawn);
};
