// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SSHUD.h"

#include "SSLogCategory.h"
#include "UI/WidgetController/SSAttributeWidgetController.h"
#include "GameFramework/PlayerState.h"
#include "UI/WidgetController/SSScoreWidgetController.h"

void ASSHUD::InitWidgets()
{
	if (!ensureMsgf(AttributeWidgetControllerClass, TEXT("AttributeWidgetControllerClass is not set in the HUD class.")))
	{
		return;
	}

	if (!ensureMsgf(ScoreWidgetControllerClass, TEXT("ScoreWidgetControllerClass is not set in the HUD class.")))
	{
		return;
	}

	if (AttributeWidgetController || ScoreWidgetController)
	{
		return;
	}

	APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		return;
	}

	const FWidgetControllerParams WidgetControllerParams{
		PlayerController,
		PlayerController->GetPlayerState<APlayerState>()
	};

	if (!WidgetControllerParams.PlayerState)
	{
		return;
	}

	AttributeWidgetController = NewObject<USSAttributeWidgetController>(this, AttributeWidgetControllerClass);
	InitializeAttributeWidget(AttributeWidgetController);

	AttributeWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	AttributeWidgetController->BindCallbacksToDependencies();
	AttributeWidgetController->BroadcastInitialValues();

	ScoreWidgetController = NewObject<USSScoreWidgetController>(this, ScoreWidgetControllerClass);
	InitializeScoreWidget(ScoreWidgetController);

	ScoreWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	ScoreWidgetController->BindCallbacksToDependencies();
	ScoreWidgetController->BroadcastInitialValues();
}
