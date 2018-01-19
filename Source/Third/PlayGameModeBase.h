// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdGameModeBase.h"
#include "PlayGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API APlayGameModeBase : public AThirdGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<class APlayerController*> PartyPlayers;


public:





public:
	FORCEINLINE TArray<class APlayerController*> GetPartyPlayer()
	{
		return PartyPlayers;
	}
	
	
	

	virtual void PostLogin(APlayerController* NewPlayer) override;

};
