// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SType.h"
#include "Interface/SkillInterface.h"
#include "Interface/SkillCastInterface.h"
#include "BaseSkill.generated.h"

UCLASS()
class THIRD_API ABaseSkill : public AActor , public ISkillInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "SkillInfo", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	struct FSkillInfo SkillInfo;

	UPROPERTY()
	class ABaseCharacter* SkillCaster;

	UPROPERTY()
	uint32 bCoolDown : 1;

	UPROPERTY()
	uint32 Casted : 1;

	UPROPERTY(Category = "HotKey", EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FKey AssingedKey;




public:
///////////////////// For  Interface   //////////////////////////////////////////
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnTrySpellCast();
	virtual void OnTrySpellCast_Implementation()				override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitializeSpellCast();
	virtual void InitializeSpellCast_Implementation()			override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSpellCast();
	virtual void OnSpellCast_Implementation()					override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCastComplete();
	virtual void OnCastComplete_Implementation()				override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCoolDownExpired();
	virtual void OnCoolDownExpired_Implementation()				override;


public:	
	// Sets default values for this actor's properties
	ABaseSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
