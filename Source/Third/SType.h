// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/DataTable.h"
#include "SType.generated.h"

/**
 * 
 */

UENUM()
enum class EPointType : uint8
{
	EPT_NULL,

	EPT_HEALTH,

	EPT_MANA,

	EPT_ENERGY,

	EPT_RAGE,

	EPT_EXP,

	EPT_MAX
};

UENUM()
enum class ESkillType : uint8
{
	EST_NULL,

	EST_MELEEATTACK,

	ESK_RANGEDATTACK,

	ESK_EXPLOSIONATTACK,

	ESK_MELEEBUFF,

	ESK_RANGEDBUFF

	
};


USTRUCT(BlueprintType)
struct FPointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxValue;

	UPROPERTY()
	float CurrentValue;
};

USTRUCT(BlueprintType)
struct FStatInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatAbility)
		int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatAbility)
		int32 Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatAbility)
		int32 Intelligence;
};


USTRUCT(BlueprintType)
struct FSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	class UTexture* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	FString SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	class UAnimMontage* Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	EPointType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	float CastingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillInfo)
	TSubclassOf<class AActor> SkillClass;

};
