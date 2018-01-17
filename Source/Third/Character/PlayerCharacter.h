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

//public:
//	//////////////////////////////////////////////////////////////////////////
//	//>									For Interface
//	UFUNCTION(BlueprintNativeEvent)
//		bool BeginFocus();
//	virtual bool BeginFocus_Implementation()									override;
//
//	UFUNCTION(BlueprintNativeEvent)
//		bool EndFocus();
//	virtual bool EndFocus_Implementation()										override;
//
//	UFUNCTION(BlueprintNativeEvent)
//		float GetUseDistance();
//	virtual float GetUseDistance_Implementation()								override;
//
//	UFUNCTION(BlueprintNativeEvent)
//		bool GetIsUsable();
//	virtual bool GetIsUsable_Implementation()									override;
//
//	UFUNCTION(BlueprintNativeEvent)
//		bool OnUsed(class APlayerController* _Controller);
//	virtual bool OnUsed_Implementation(APlayerController* _Controller)			override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void BeginSpellCast();
	virtual void BeginSpellCast_Implementation()		override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EndSpellCast();
	virtual void EndSpellCast_Implementation()			override;
	
	
	
};
