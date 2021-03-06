// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API ACustomAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class ABaseCharacter* CustomCharacter;
	
	
	
	
public:
	virtual void Possess(APawn* InPawn) override;


	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;

};
