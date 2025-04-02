// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSBaseProjectile.h"
#include "SSBulletProjectile.generated.h"

class USSAction;

UCLASS()
class SIMPLESHOOTER_API ASSBulletProjectile : public ASSBaseProjectile
{
	GENERATED_BODY()

public:
	ASSBulletProjectile();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TSubclassOf<USSAction> ActionDamageClass;
};
