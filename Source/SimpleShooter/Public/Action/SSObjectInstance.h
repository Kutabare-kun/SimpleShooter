// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SSObjectInstance.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SIMPLESHOOTER_API USSObjectInstance : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override { return true; }

	virtual UWorld* GetWorld() const override final;
	APawn* GetPawn() const;

	FORCEINLINE void SetInstigator(UObject* InInstigator) { Instigator = InInstigator; }
	FORCEINLINE UObject* GetInstigator() const { return Instigator; }

private:
	UPROPERTY(Replicated)
	TObjectPtr<UObject> Instigator;
};
