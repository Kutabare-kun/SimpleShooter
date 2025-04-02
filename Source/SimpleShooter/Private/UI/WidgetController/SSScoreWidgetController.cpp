// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SSScoreWidgetController.h"

#include "Player/SSPlayerState.h"

void USSScoreWidgetController::BroadcastInitialValues()
{
	const ASSPlayerState* PS = Cast<ASSPlayerState>(PlayerState);
	if (!PS)
	{
		return;
	}

	PS->OnScoreChanged.Broadcast(PS->GetScore());
}

void USSScoreWidgetController::BindCallbacksToDependencies()
{
	ASSPlayerState* PS = Cast<ASSPlayerState>(PlayerState);
	if (!PS)
	{
		return;
	}

	PS->OnScoreChanged.AddUniqueDynamic(this, &ThisClass::OnScoreChanged);
}
