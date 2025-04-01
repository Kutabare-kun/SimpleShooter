// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/SSUserWidget.h"

void USSUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (!InWidgetController)
	{
		return;
	}

	WidgetController = InWidgetController;
	WidgetControllerSet();
}
