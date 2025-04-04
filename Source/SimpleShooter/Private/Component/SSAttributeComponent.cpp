// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SSAttributeComponent.h"

#include "SimpleShooterGameMode.h"
#include "SSLogCategory.h"
#include "Net/UnrealNetwork.h"
#include "Player/SSPlayerController.h"

USSAttributeComponent::USSAttributeComponent()
{
	HealthMax = Health = 100.0f;
	AmmoMax = Ammo = 0.0f;

	SetIsReplicatedByDefault(true);
}

bool USSAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	const float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	const float ActualDelta = NewHealth - Health;

	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			OnDeath(InstigatorActor);
		}

		if (InstigatorActor != GetOwner())
		{
			MakeDamageFeedback(InstigatorActor, ActualDelta);
		}
	}

	return ActualDelta != 0;
}

void USSAttributeComponent::OnDeath(AActor* Instigator) const
{
	ASimpleShooterGameMode* GameMode = Cast<ASimpleShooterGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}

	GameMode->OnKillActor(GetOwner(), Instigator);
}

void USSAttributeComponent::MakeDamageFeedback(AActor* Instigator, const float Damage) const
{
	const APawn* ThisPawn = Cast<APawn>(Instigator);
	if (!ThisPawn)
	{
		return;
	}

	ASSPlayerController* PC = Cast<ASSPlayerController>(ThisPawn->GetController());
	if (!PC)
	{
		return;
	}

	PC->ClientShowDamage(GetOwner(), Damage);
}

bool USSAttributeComponent::ApplyAmmoChange(const float Delta)
{
	if (Delta > Ammo)
	{
		return false;
	}

	const float NewAmmo = FMath::Clamp(Ammo + Delta, 0.0f, AmmoMax);
	const float ActualDelta = NewAmmo - Ammo;

	if (GetOwner()->HasAuthority())
	{
		const float OldAmmo = Ammo;
		Ammo = NewAmmo;

		if (ActualDelta != 0.0f)
		{
			OnRep_Ammo(OldAmmo);
		}
	}

	return ActualDelta != 0.0f;
}

void USSAttributeComponent::InitializeAmmo(const float InAmmo, const float InAmmoMax)
{
	const float OldAmmoMax = AmmoMax;
	const float OldAmmo = Ammo;

	AmmoMax = InAmmoMax;
	Ammo = InAmmo;

	OnAmmoChanged.Broadcast(GetOwner(), this, Ammo, Ammo - OldAmmo);
	OnAmmoMaxChanged.Broadcast(GetOwner(), this, InAmmoMax, AmmoMax - OldAmmoMax);
}

void USSAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, const float NewValue, const float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewValue, Delta);
}

void USSAttributeComponent::OnRep_Ammo(const float OldAmmo)
{
	OnAmmoChanged.Broadcast(GetOwner(), this, Ammo, Ammo - OldAmmo);
}

void USSAttributeComponent::OnRep_AmmoMax(const float OldAmmoMax)
{
	OnAmmoMaxChanged.Broadcast(GetOwner(), this, AmmoMax, AmmoMax - OldAmmoMax);
}

void USSAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Health);
	DOREPLIFETIME(ThisClass, HealthMax);

	DOREPLIFETIME_CONDITION(ThisClass, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ThisClass, AmmoMax, COND_OwnerOnly);
}
