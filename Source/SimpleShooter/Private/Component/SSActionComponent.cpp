// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSActionComponent.h"

#include "Action/SSAction.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

USSActionComponent::USSActionComponent()
{
	SetIsReplicatedByDefault(true);
}

void USSActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	for (const TSubclassOf<USSAction>& ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}

void USSActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TArray<TObjectPtr<USSAction>> ActionCopy = Actions;
	for (const TObjectPtr<USSAction>& Action : ActionCopy)
	{
		if (Action && Action->IsRunning())
		{
			Action->StopAction(GetOwner());
		}
	}

	Super::EndPlay(EndPlayReason);
}

bool USSActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool Bits = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for (TObjectPtr<USSAction>& Action : Actions)
	{
		if (!Action)
		{
			continue;
		}

		Bits |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
	}

	return Bits;
}

void USSActionComponent::AddAction(AActor* InInstigator, const TSubclassOf<USSAction> ActionClass)
{
	if (!ActionClass)
	{
		return;
	}

	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	USSAction* NewAction = NewObject<USSAction>(GetOwner(), ActionClass);
	if (!NewAction)
	{
		return;
	}

	NewAction->Initialize(this);
	Actions.Add(NewAction);

	if (NewAction->IsAutoStart() && NewAction->CanStartAction())
	{
		NewAction->StartAction(InInstigator);
	}
}

void USSActionComponent::RemoveAction(USSAction* ActionToRemove)
{
	if (!ActionToRemove || ActionToRemove->IsRunning())
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

USSAction* USSActionComponent::GetAction(const TSubclassOf<USSAction> ActionClass) const
{
	for (USSAction* Action : Actions)
	{
		if (!Action || !Action->IsA(ActionClass))
		{
			continue;
		}

		return Action;
	}

	return nullptr;
}

bool USSActionComponent::StartActionByTag(AActor* Instigator, const FGameplayTag& ActionTag)
{
	for (const TObjectPtr<USSAction>& Action : Actions)
	{
		if (Action && Action->GetActionTag().MatchesTag(ActionTag))
		{
			if (!Action->CanStartAction())
			{
				continue;
			}

			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionTag);
			}

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool USSActionComponent::StopActionByTag(AActor* Instigator, const FGameplayTag& ActionTag)
{
	for (const TObjectPtr<USSAction>& Action : Actions)
	{
		if (!Action || !Action->GetActionTag().MatchesTag(ActionTag))
		{
			continue;
		}

		if (!Action->IsRunning())
		{
			continue;
		}

		if (!GetOwner()->HasAuthority())
		{
			ServerStopAction(Instigator, ActionTag);
		}

		Action->StopAction(Instigator);
		return true;
	}

	return false;
}

void USSActionComponent::ServerStartAction_Implementation(AActor* Instigator, const FGameplayTag& ActionTag)
{
	StartActionByTag(Instigator, ActionTag);
}

void USSActionComponent::ServerStopAction_Implementation(AActor* Instigator, const FGameplayTag& ActionTag)
{
	StopActionByTag(Instigator, ActionTag);
}

void USSActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Actions);
}
