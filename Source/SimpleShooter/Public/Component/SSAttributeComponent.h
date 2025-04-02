// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, USSAttributeComponent*, OwningComp, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USSAttributeComponent();

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttributeChanged OnAmmoMaxChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttributeChanged OnAmmoChanged;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE float GetHealthMax() const { return HealthMax; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE bool IsAlive() const { return Health > 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE bool IsHealthFull() const { return Health >= HealthMax; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void InitializeAmmo(const float InAmmo, const float InAmmoMax);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyAmmoChange(const float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE float GetAmmo() const { return Ammo; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE float GetAmmoMax() const { return AmmoMax; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE bool IsAmmoFull() const { return Ammo >= AmmoMax; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	FORCEINLINE bool IsAmmoEmpty() const { return Ammo <= 0.0f; }

protected:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor* InstigatorActor, const float NewValue, const float Delta);

	UFUNCTION()
	void OnRep_Ammo(const float OldAmmo);

	UFUNCTION()
	void OnRep_AmmoMax(const float OldAmmoMax);

	void OnDeath(AActor* Instigator) const;

	void MakeDamageFeedback(AActor* Instigator, const float Damage) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
	float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing = "OnRep_Ammo", Category = "Attributes")
	float Ammo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing = "OnRep_AmmoMax", Category = "Attributes")
	float AmmoMax;
};
