// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerController.h"

#include "SSLogCategory.h"
#include "Component/SSDamageTextComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/HUD/SSHUD.h"

void ASSPlayerController::InitOverlay() const
{
	ASSHUD* ThisHUD = GetHUD<ASSHUD>();
	if (!ThisHUD)
	{
		return;
	}

	ThisHUD->InitWidgets();
}

void ASSPlayerController::UpdateOverlay() const
{
	const ASSHUD* ThisHUD = GetHUD<ASSHUD>();
	if (!ThisHUD)
	{
		return;
	}

	ThisHUD->UpdateBindWidgets();
}

void ASSPlayerController::ClientShowDamage_Implementation(AActor* Target, const float DamageAmount)
{
	if (!Target)
	{
		return;
	}

	if (!DamageTextComponentClass)
	{
		SS_LOG(LogController, Error, TEXT("DamageTextComponentClass is not set."))
		return;
	}

	const APawn* ThisPawn = GetPawn();
	if (!ThisPawn)
	{
		return;
	}

	USSDamageTextComponent* DamageTextComponent = NewObject<USSDamageTextComponent>(Target, DamageTextComponentClass);
	DamageTextComponent->RegisterComponent();
	DamageTextComponent->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	DamageTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DamageTextComponent->SetDamage(DamageAmount);

	const FVector ViewLocation = ThisPawn->GetPawnViewLocation();
	const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(DamageTextComponent->GetComponentLocation(), ViewLocation);
	DamageTextComponent->SetRelativeRotation(TargetRotation);
}

void ASSPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitOverlay();
}

void ASSPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	InitOverlay();
}

void ASSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UpdateOverlay();
}

void ASSPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	UpdateOverlay();
}
