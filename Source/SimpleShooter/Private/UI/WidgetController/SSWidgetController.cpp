// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SSWidgetController.h"

void USSWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
}
