// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillCastInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkillCastInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THIRD_API ISkillCastInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginSpellCast();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndSpellCast();
};
