// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/SkillCastInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API APlayerCharacter : public ABaseCharacter , public ISkillCastInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginSpellCast();
	virtual void BeginSpellCast_Implementation()		override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndSpellCast();
	virtual void EndSpellCast_Implementation()			override;
	
	
	
};
