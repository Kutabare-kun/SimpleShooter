// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SSInteractWidgetComponent.generated.h"

class ASSPowerUp;

UCLASS()
class SIMPLESHOOTER_API USSInteractWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void SetInteractable(ASSPowerUp* InPowerUp);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<UDataTable> InteractableDataTable;
};
