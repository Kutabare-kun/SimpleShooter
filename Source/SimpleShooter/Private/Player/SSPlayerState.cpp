// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState.h"

void ASSPlayerState::OnRep_Score()
{
	OnScoreChanged.Broadcast(GetScore());
}
