// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/Public/PowerUp/SSPowerUp.h"

#include "Components/SphereComponent.h"

ASSPowerUp::ASSPowerUp()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);

	SetReplicates(true);
}
