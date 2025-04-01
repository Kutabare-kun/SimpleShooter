// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSInteractionComponent.generated.h"


class USSInteractionHelperManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USSInteractionComponent();

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void FindTargetActor(APawn* InOwner);

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InTargetActor);

protected:
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Interaction")
	TObjectPtr<USSInteractionHelperManager> HelperManager;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float TraceDistance = 1250.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float TraceRadius = 24.0f;

private:
	TWeakObjectPtr<AActor> TargetActor;
};
