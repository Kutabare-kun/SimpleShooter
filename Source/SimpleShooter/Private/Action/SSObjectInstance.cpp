// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SSObjectInstance.h"

#include "Net/UnrealNetwork.h"

UWorld* USSObjectInstance::GetWorld() const
{
	const APawn* OwningPawn = GetPawn();
	return OwningPawn ? OwningPawn->GetWorld() : nullptr;
}

APawn* USSObjectInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

void USSObjectInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Instigator);
}
