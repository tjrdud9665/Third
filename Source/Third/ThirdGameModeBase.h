// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API AThirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		

	
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;




};
