// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SSAction_Attack.h"

#include "SSLogCategory.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/SSBaseProjectile.h"

void USSAction_Attack::StartAction_Implementation(AActor* InInstigator)
{
	Super::StartAction_Implementation(InInstigator);

	ACharacter* ThisCharacter = Cast<ACharacter>(InInstigator);
	if (!ThisCharacter)
	{
		return;
	}

	if (!ThisCharacter->HasAuthority())
	{
		return;
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ThisClass::AttackDelay_Elapsed, ThisCharacter);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, TimerDelegate, AttackDelay, false);
}

void USSAction_Attack::AttackDelay_Elapsed_Implementation(ACharacter* InCharacter)
{
	if (!ProjectileClass)
	{
		SS_LOG(LogSSAction, Error, TEXT("ProjectileClass is not set"));
		StopAction(InCharacter);
		return;
	}

	const FVector SocketLocation = InCharacter->GetMesh()->GetSocketLocation(ActionSocketName);
	const FVector ImpactPoint = MakeImpactPoint(InCharacter);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = InCharacter;

	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(SocketLocation, ImpactPoint);
	const FTransform SpawnTransform = FTransform(TargetRotation, SocketLocation);
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);

	StopAction(InCharacter);
}

FVector USSAction_Attack::MakeImpactPoint(ACharacter* InCharacter) const
{
	const FVector TraceStart = InCharacter->GetPawnViewLocation();
	const FVector TraceEnd = TraceStart + InCharacter->GetControlRotation().Vector() * TraceRange;

	const FCollisionShape Sphere = FCollisionShape::MakeSphere(TraceRadius);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(InCharacter);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FHitResult Hit;
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Sphere, Params))
	{
		return Hit.ImpactPoint;
	}

	return TraceEnd;
}
