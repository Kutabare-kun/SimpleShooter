// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/SSInteractionWorldWidget.h"

#include "Camera/CameraComponent.h"
#include "Component/SSInteractWidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PowerUp/SSPowerUp.h"

void USSInteractionWorldWidget::Interaction_Implementation(APawn* InOwner, AActor* InTargetActor)
{
	if (!ensureMsgf(InteractWidgetClass, TEXT("InteractWidgetClass is not set in %s"), *GetName()))
	{
		return;
	}

	if (!CachedTargetActor.IsValid() || CachedTargetActor != InTargetActor)
	{
		CachedTargetActor = InTargetActor;

		if (InteractWidgetComponent)
		{
			InteractWidgetComponent->SetVisibility(false);
			InteractWidgetComponent->DestroyComponent();
			InteractWidgetComponent = nullptr;
		}
	}

	if (!InteractWidgetComponent)
	{
		InteractWidgetComponent = NewObject<USSInteractWidgetComponent>(InTargetActor, InteractWidgetClass);
		InteractWidgetComponent->RegisterComponent();
		InteractWidgetComponent->AttachToComponent(InTargetActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		InteractWidgetComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}

	ASSPowerUp* PowerUp = Cast<ASSPowerUp>(InTargetActor);
	if (!PowerUp) return;

	const UCameraComponent* CameraComponent = InOwner->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent) return;

	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(InteractWidgetComponent->GetComponentLocation(), CameraComponent->GetComponentLocation());
	InteractWidgetComponent->SetRelativeRotation(TargetRotation);

	InteractWidgetComponent->SetInteractable(PowerUp);
	InteractWidgetComponent->SetVisibility(true);

	const UWorld* ThisWorld = InOwner->GetWorld();
	if (!ThisWorld) return;

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]()
	{
		if (InteractWidgetComponent)
		{
			InteractWidgetComponent->SetVisibility(false);
		}
	});

	ThisWorld->GetTimerManager().SetTimer(TimerHandle_Interaction, TimerDelegate, TimerInterval, false);
}
