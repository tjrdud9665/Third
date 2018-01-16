// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayGameModeBase.h"




void APlayGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PartyPlayers.Add(NewPlayer);

}
