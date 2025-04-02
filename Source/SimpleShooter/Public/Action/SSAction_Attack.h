// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SSAction.h"
#include "SSAction_Attack.generated.h"

class ASSBaseProjectile;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSAction_Attack : public USSAction
{
	GENERATED_BODY()

public:
	virtual void StartAction_Implementation(AActor* InInstigator) override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void AttackDelay_Elapsed(ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category="Action")
	FVector MakeImpactPoint(ACharacter* InCharacter) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<ASSBaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	FName ActionSocketName = "AttackSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float TraceRange = 2500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float TraceRadius = 24.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	float AttackDelay = 0.5f;

	FTimerHandle TimerHandle_AttackDelay;
};
