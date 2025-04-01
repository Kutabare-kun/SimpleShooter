// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSWidgetController.h"
#include "SSAttributeWidgetController.generated.h"

class USSAttributeComponent;

UCLASS(BlueprintType, Blueprintable)
class SIMPLESHOOTER_API USSAttributeWidgetController : public USSWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void OnHealthChanged(AActor* Instigator, USSAttributeComponent* OwningComponent, float NewValue, float Delta);

	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void OnAmmoChanged(AActor* Instigator, USSAttributeComponent* OwningComponent, float NewValue, float Delta);

	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void OnAmmoMaxChanged(AActor* Instigator, USSAttributeComponent* OwningComponent, float NewValue, float Delta);
};
