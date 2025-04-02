// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSWidgetController.h"
#include "SSScoreWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SIMPLESHOOTER_API USSScoreWidgetController : public USSWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void OnScoreChanged(int32 NewScore);
};
