// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/InteractableInterface.h"
#include "Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"




UCLASS()
class THIRD_API ABaseCharacter : public ACharacter , public IInteractableInterface , public ICombatInterface
{
	GENERATED_BODY()

private:
//////////////////////////////////////////////////////////////////////////
//>									For Componetns
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointComponent* PointComp;

//////////////////////////////////////////////////////////////////////////
//> Custom Controller
	UPROPERTY()
	class AController* CustomPlayerController;



	/////////////////   For Interaction			/////////////////////////////
	UPROPERTY()
	uint32 bHostile : 1;

	UPROPERTY()
	uint32 bUsable : 1;

	UPROPERTY()
	float UseDistance;

	UPROPERTY(Category = "Character Stat", EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;
	///////////////		For Combat	//////////////////////
	UPROPERTY()
	uint32 bAttacking : 1;

	UPROPERTY()
	uint32 bAlive : 1;

	UPROPERTY()
	uint32 bMovable : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DefaultMelleAttack", meta = (AllowPrivateAccess = "true"))
	float MelleAttackDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DefaultMelleAttack", meta = (AllowPrivateAccess = "true"))
	float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HitAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* DefaultAttackAnim;



public:
	UFUNCTION()
	void DefaultAttack();

	UFUNCTION()
	void SetMoveable(bool _NewMovable);

public:
	UFUNCTION()
	void SetPlayerController(class AController* _Controller);

	


public:
	//////////////////////////////////////////////////////////////////////////
	//>									For Interface
	UFUNCTION(BlueprintNativeEvent)
	bool BeginFocus();
	virtual bool BeginFocus_Implementation()									override;

	UFUNCTION(BlueprintNativeEvent)
	bool EndFocus();
	virtual bool EndFocus_Implementation()										override;

	UFUNCTION(BlueprintNativeEvent)
	float GetUseDistance();
	virtual float GetUseDistance_Implementation()								override;

	UFUNCTION(BlueprintNativeEvent)
	bool GetIsUsable();
	virtual bool GetIsUsable_Implementation()									override;

	UFUNCTION(BlueprintNativeEvent)
	bool OnUsed(class APlayerController* _Controller);
	virtual bool OnUsed_Implementation(APlayerController* _Controller)			override;

	UFUNCTION(BlueprintNativeEvent)
	bool GetIsHostil();
	virtual bool GetIsHostil_Implementation()										override;

	
	UFUNCTION(BlueprintNativeEvent)
	bool GetIsAlive();
	virtual bool GetIsAlive_Implementation()									override;


	UFUNCTION(BlueprintNativeEvent)
	float GetAttackRange();
	virtual float GetAttackRange_Implementation()									override;

	UFUNCTION(BlueprintNativeEvent)
		float GetAttackDamage();
	virtual float GetAttackDamage_Implementation()									override;


	//////////////////////////////////////////////////////////////////////////
	//>									For Interaction
	UFUNCTION(Category = "Interaction")
	float GetTargetDistance(AActor* Target);


public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	FORCEINLINE UPointComponent* GetPointComp()
	{
		return PointComp;
	}

	FORCEINLINE uint32 IsMovable()
	{
		return bMovable;
	}

	FORCEINLINE float GetDefaultMelleDistance()
	{
		return MelleAttackDistance;
	}
	FORCEINLINE class AController* GetCustomController()
	{
		return CustomPlayerController;
	}
};
