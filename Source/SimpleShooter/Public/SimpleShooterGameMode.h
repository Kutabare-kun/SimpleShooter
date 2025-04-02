// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterGameMode.generated.h"

UCLASS(minimalapi)
class ASimpleShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleShooterGameMode();

	void OnKillActor(AActor* Victim, AActor* Killer);

protected:
	void RespawnPlayer_Elapsed(AController* InController);
};



