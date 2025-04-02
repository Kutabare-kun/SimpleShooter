// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSHUD.generated.h"

class USSWidgetController;
class USSScoreWidgetController;
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
	void InitWidgets();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void InitializeAttributeWidget(USSWidgetController* InWidgetController);

	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetController")
	void InitializeScoreWidget(USSWidgetController* InWidgetController);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSAttributeWidgetController> AttributeWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USSAttributeWidgetController> AttributeWidgetController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetController", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSScoreWidgetController> ScoreWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USSScoreWidgetController> ScoreWidgetController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSUserWidget> AttributeWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USSUserWidget> ScoreWidgetClass;
};
