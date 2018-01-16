// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownPawn.generated.h"

UCLASS()
class THIRD_API ATopDownPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownPawn();

private:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	FORCEINLINE class UCameraComponent* GetTopDownCamera()
	{
		return TopDownCamera;
	}

	FORCEINLINE class USpringArmComponent* GetCameraBoom()
	{
		return CameraBoom;
	}


	
	
};
