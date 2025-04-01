// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SSHUD.h"

#include "UI/WidgetController/SSAttributeWidgetController.h"
#include "GameFramework/PlayerState.h"

void ASSHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!ensureMsgf(AttributeWidgetControllerClass, TEXT("AttributeWidgetControllerClass is not set in the HUD class.")))
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

	AttributeWidgetController = NewObject<USSAttributeWidgetController>(this, AttributeWidgetControllerClass);
	InitializeAttributeWidget(AttributeWidgetController);

	AttributeWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	AttributeWidgetController->BindCallbacksToDependencies();
	AttributeWidgetController->BroadcastInitialValues();
}
