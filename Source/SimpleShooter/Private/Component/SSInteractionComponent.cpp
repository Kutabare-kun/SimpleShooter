// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSInteractionComponent.h"

#include "Interaction/SSInteractionHelperManager.h"
#include "Interface/SSInteraction.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("SS.DebugDrawInteraction"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

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

	const bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 1.0f);
	}

	if (bHit)
	{
		for (const FHitResult& Result : Hits)
		{
			if (AActor* HitActor = Result.GetActor();
				HitActor->Implements<USSInteraction>())
			{
				if (bDebugDraw)
				{
					DrawDebugSphere(GetWorld(), Result.ImpactPoint, TraceRadius, 12, FColor::Blue, false, 0.1f);
				}

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
