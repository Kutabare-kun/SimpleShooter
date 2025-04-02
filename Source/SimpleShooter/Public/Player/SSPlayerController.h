// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController.generated.h"

class USSDamageTextComponent;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void ClientInitOverlay();

	UFUNCTION(Client, Reliable)
	void ClientShowDamage(AActor* Target, const float DamageAmount);

	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlayingState() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TSubclassOf<USSDamageTextComponent> DamageTextComponentClass;
};
