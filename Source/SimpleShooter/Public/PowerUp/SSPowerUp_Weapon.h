// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp/SSPowerUp.h"
#include "SSPowerUp_Weapon.generated.h"

class USSAction;

UCLASS()
class SIMPLESHOOTER_API ASSPowerUp_Weapon : public ASSPowerUp
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PowerUp")
	TSubclassOf<USSAction> WeaponActionClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PowerUp")
	TSubclassOf<USSAction> WeaponAmmoActionClass;
};
