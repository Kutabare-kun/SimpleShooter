// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleShooterGameMode.h"
#include "SimpleShooterCharacter.h"
#include "SSLogCategory.h"
#include "GameFramework/PlayerState.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ASimpleShooterGameMode::ASimpleShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASimpleShooterGameMode::OnKillActor(AActor* Victim, AActor* Killer)
{
	SS_LOG(LogGameMode, Log, TEXT("KillActor Victim: %s Killer: %s"), *GetNameSafe(Victim), *GetNameSafe(Killer));

	const APawn* VictimPawn = Cast<APawn>(Victim);
	if (!VictimPawn)
	{
		return;
	}

	const APawn* KillerPawn = Cast<APawn>(Killer);
	if (!KillerPawn)
	{
		return;
	}

	FTimerHandle TimerHandle_RespawnDelay;
	FTimerDelegate TimerDelegate_RespawnDelay;
	TimerDelegate_RespawnDelay.BindUObject(this, &ThisClass::RespawnPlayer_Elapsed, VictimPawn->GetController());

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, TimerDelegate_RespawnDelay, 10.0f, false);

	ASSPlayerState* PSKiller = KillerPawn->GetPlayerState<ASSPlayerState>();
	if (!PSKiller)
	{
		return;
	}

	PSKiller->SetScore(PSKiller->GetScore() + 1);

	// For Server
	PSKiller->OnScoreChanged.Broadcast(PSKiller->GetScore());
}

void ASimpleShooterGameMode::RespawnPlayer_Elapsed(AController* InController)
{
	if (!InController)
	{
		SS_LOG(LogGameMode, Error, TEXT("InController is not valid"));
		return;
	}

	InController->UnPossess();
	RestartPlayer(InController);
}
