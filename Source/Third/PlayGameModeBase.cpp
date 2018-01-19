// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayGameModeBase.h"
#include "Controller/CustomPlayerController.h"


void APlayGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PartyPlayers.Add(NewPlayer);

}
