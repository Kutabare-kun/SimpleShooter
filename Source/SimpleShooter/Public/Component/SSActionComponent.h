// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SSActionComponent.generated.h"

class USSAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, USSActionComponent*, OwningComp, USSAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USSActionComponent();

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActionStateChanged OnActionStopped;

public:
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void AddAction(AActor* InInstigator, const TSubclassOf<USSAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(USSAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	USSAction* GetAction(const TSubclassOf<USSAction> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByTag(AActor* Instigator, const FGameplayTag& ActionTag);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByTag(AActor* Instigator, const FGameplayTag& ActionTag);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

private:
	UFUNCTION(Server, Reliable)
	void ServerStartAction(AActor* Instigator, const FGameplayTag& ActionTag);

	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* Instigator, const FGameplayTag& ActionTag);

	UPROPERTY(Replicated)
	TArray<TObjectPtr<USSAction>> Actions;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TArray<TSubclassOf<USSAction>> DefaultActions;

	friend USSAction;
};
