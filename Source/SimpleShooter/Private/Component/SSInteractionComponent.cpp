// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSInteractionComponent.h"

#include "Interaction/SSInteractionHelperManager.h"
#include "Interface/SSInteraction.h"

USSInteractionComponent::USSInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (APawn* ThisPawn = Cast<APawn>(GetOwner());
		ThisPawn->IsLocallyControlled())
	{
		FindTargetActor(ThisPawn);
	}
}

void USSInteractionComponent::FindTargetActor(APawn* InOwner)
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InOwner);

	const FVector TraceStart = InOwner->GetPawnViewLocation();
	const FRotator TraceRotation = InOwner->GetControlRotation();
	const FVector TraceEnd = TraceStart + TraceRotation.Vector() * TraceDistance;

	TArray<FHitResult> Hits;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(TraceRadius);
	const bool bHit = GetWorld()->SweepMultiByObjectType(
		Hits,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ObjectQueryParams,
		Sphere,
		CollisionParams
	);

	if (bHit)
	{
		for (const FHitResult& Result : Hits)
		{
			if (AActor* HitActor = Result.GetActor();
				HitActor->Implements<USSInteraction>())
			{
				TargetActor = HitActor;
				break;
			}
		}

		if (TargetActor.IsValid() && HelperManager)
		{
			HelperManager->Interaction(InOwner, TargetActor.Get());
		}
	}
}

void USSInteractionComponent::Interact()
{
	if (TargetActor.IsValid())
	{
		ServerInteract(TargetActor.Get());
	}
}

void USSInteractionComponent::ServerInteract_Implementation(AActor* InTargetActor)
{
	if (!InTargetActor)
	{
		return;
	}

	ISSInteraction::Execute_Interact(InTargetActor, static_cast<APawn*>(GetOwner()));
}
