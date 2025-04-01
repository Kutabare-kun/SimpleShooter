// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SSAttributeWidgetController.h"

#include "Component/SSAttributeComponent.h"

void USSAttributeWidgetController::BroadcastInitialValues()
{
	APawn* ThisPawn = PlayerController->GetPawn();
	if (!ThisPawn)
	{
		return;
	}

	USSAttributeComponent* AttributeComponent = ThisPawn->GetComponentByClass<USSAttributeComponent>();
	if (!AttributeComponent)
	{
		return;
	}

	AttributeComponent->OnHealthChanged.Broadcast(ThisPawn, AttributeComponent, AttributeComponent->GetHealth(), 0.0f);
	AttributeComponent->OnAmmoChanged.Broadcast(ThisPawn, AttributeComponent, AttributeComponent->GetAmmo(), 0.0f);
	AttributeComponent->OnAmmoMaxChanged.Broadcast(ThisPawn, AttributeComponent, AttributeComponent->GetAmmoMax(), 0.0f);
}

void USSAttributeWidgetController::BindCallbacksToDependencies()
{
	const APawn* ThisPawn = PlayerController->GetPawn();
	if (!ThisPawn)
	{
		return;
	}

	USSAttributeComponent* AttributeComponent = ThisPawn->GetComponentByClass<USSAttributeComponent>();
	if (!AttributeComponent)
	{
		return;
	}

	AttributeComponent->OnHealthChanged.AddUniqueDynamic(this, &ThisClass::OnHealthChanged);
	AttributeComponent->OnAmmoChanged.AddUniqueDynamic(this, &ThisClass::OnAmmoChanged);
	AttributeComponent->OnAmmoMaxChanged.AddUniqueDynamic(this, &ThisClass::OnAmmoMaxChanged);
}
