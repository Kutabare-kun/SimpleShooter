// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSHUD.generated.h"

class USSUserWidget;
class USSAttributeWidgetController;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void InitializeAttributeWidget(USSAttributeWidgetController* InWidgetController);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSAttributeWidgetController> AttributeWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USSAttributeWidgetController> AttributeWidgetController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSUserWidget> UserWidgetClass;
};
