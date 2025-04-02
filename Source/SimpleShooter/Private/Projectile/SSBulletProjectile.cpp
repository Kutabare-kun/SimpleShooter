// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SSBulletProjectile.h"

#include "SSLogCategory.h"
#include "Action/SSAction.h"
#include "Component/SSActionComponent.h"
#include "Components/SphereComponent.h"

ASSBulletProjectile::ASSBulletProjectile()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComponent->SetupAttachment(GetRootComponent());
}

void ASSBulletProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetInstigator())
	{
		return;
	}

	USSActionComponent* ActionComponent = OtherActor->GetComponentByClass<USSActionComponent>();
	if (!ActionComponent)
	{
		return;
	}

	if (!ActionDamageClass)
	{
		SS_LOG(LogSSBaseProjectile, Error, TEXT("ActionDamageClass is not set in %s"), *GetName());
		return;
	}

	Destroy();
	ActionComponent->AddAction(GetInstigator(), ActionDamageClass);
}

void ASSBulletProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBeginOverlap);
}
