// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SSDamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category="DamageText")
	void SetDamage(const float Damage);
};
