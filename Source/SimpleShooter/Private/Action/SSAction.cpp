// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SSAction.h"

#include "Component/SSActionComponent.h"
#include "Net/UnrealNetwork.h"

void USSAction::Initialize(USSActionComponent* InActionComponent)
{
	ActionComponent = InActionComponent;
}

bool USSAction::CanStartAction_Implementation()
{
	if (bIsRunning)
	{
		return false;
	}

	const USSActionComponent* Component = GetOwningComponent();
	return !Component->ActiveGameplayTags.HasAny(BlockedTags);
}

void USSAction::StartAction_Implementation(AActor* InInstigator)
{
	bIsRunning = true;
	SetInstigator(InInstigator);

	USSActionComponent* Component = GetOwningComponent();
	Component->ActiveGameplayTags.AppendTags(GrantedTags);

	Component->OnActionStarted.Broadcast(Component, this);
}

void USSAction::StopAction_Implementation(AActor* InInstigator)
{
	bIsRunning = false;

	USSActionComponent* Component = GetOwningComponent();
	Component->ActiveGameplayTags.RemoveTags(GrantedTags);

	Component->OnActionStopped.Broadcast(Component, this);
}

void USSAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USSAction, bIsRunning);
	DOREPLIFETIME(USSAction, ActionComponent);
}
