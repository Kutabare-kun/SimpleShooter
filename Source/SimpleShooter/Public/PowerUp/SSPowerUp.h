// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interface/SSInteraction.h"
#include "SSPowerUp.generated.h"

class USphereComponent;

USTRUCT(BlueprintType, Blueprintable)
struct FPowerUpInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PowerUp")
	FGameplayTag PowerUpTag; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PowerUp")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PowerUp")
	FText Description;
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class SIMPLESHOOTER_API ASSPowerUp : public AActor, public ISSInteraction
{
	GENERATED_BODY()

public:
	ASSPowerUp();

	UFUNCTION(BlueprintCallable, Category="PowerUp")
	FORCEINLINE FGameplayTag GetPowerUpTag() const { return PowerUpTag; }

protected:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override PURE_VIRTUAL(&ThisClass::Interact_Implementation, );

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PowerUp")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PowerUp")
	FGameplayTag PowerUpTag; 
};
