// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SSBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASSBaseProjectile::ASSBaseProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	SetRootComponent(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->SetUpdatedComponent(SphereComponent);
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->InitialSpeed = 3000.f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 30.0f;

	bReplicates = true;
}

void ASSBaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	MovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);

	Destroy();
}

void ASSBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnHit);
}



