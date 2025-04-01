// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/SSInteractionHelper.h"
#include "SSInteractionWorldWidget.generated.h"

class USSInteractWidgetComponent;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSInteractionWorldWidget : public USSInteractionHelper
{
	GENERATED_BODY()

public:
	virtual void Interaction_Implementation(APawn* InOwner, AActor* InTargetActor) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	TSubclassOf<USSInteractWidgetComponent> InteractWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	float TimerInterval = 1.0f;

	UPROPERTY()
	TObjectPtr<USSInteractWidgetComponent> InteractWidgetComponent;

	TWeakObjectPtr<AActor> CachedTargetActor;

	FTimerHandle TimerHandle_Interaction;
};
