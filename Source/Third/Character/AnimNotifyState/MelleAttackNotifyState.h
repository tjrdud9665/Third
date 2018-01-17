// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MelleAttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API UMelleAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ABaseCharacter* OwnerCharacter;
	
	UPROPERTY()
	FTimerHandle HitTraceTimer;

	UPROPERTY()
	TArray<AActor*> DamagedActor;


	
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

	void GenerateLineTrace();

};
