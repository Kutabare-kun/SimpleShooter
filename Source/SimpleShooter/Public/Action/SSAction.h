// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Action/SSObjectInstance.h"
#include "SSAction.generated.h"

class USSActionComponent;

UCLASS(Blueprintable)
class SIMPLESHOOTER_API USSAction : public USSObjectInstance
{
	GENERATED_BODY()

public:
	void Initialize(USSActionComponent* InActionComponent);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStartAction();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* InInstigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StopAction(AActor* InInstigator);

	UFUNCTION(BlueprintCallable, Category = "Action")
	FORCEINLINE bool IsRunning() const { return bIsRunning; }

	UFUNCTION(BlueprintCallable, Category = "Action")
	FORCEINLINE bool IsAutoStart() const { return bAutoStart; }

	UFUNCTION(BlueprintCallable, Category = "Action")
	FORCEINLINE FGameplayTag GetActionTag() const { return ActionTag; }

protected:
	UFUNCTION(BlueprintCallable, Category = "Action")
	FORCEINLINE USSActionComponent* GetOwningComponent() const { return ActionComponent; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action");
	FGameplayTag ActionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action");
	FGameplayTagContainer GrantedTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action");
	FGameplayTagContainer BlockedTags;

	UPROPERTY(Replicated)
	bool bIsRunning = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action");
	bool bAutoStart = false;

private:
	UPROPERTY(Replicated)
	TObjectPtr<USSActionComponent> ActionComponent;
};
