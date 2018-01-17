// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomAIController.h"
#include "Character/BaseCharacter.h"



void ACustomAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	CustomCharacter = Cast<ABaseCharacter>(InPawn);


	
}

FPathFollowingRequestResult ACustomAIController::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath /*= nullptr*/)
{
	if (CustomCharacter->IsMovable())
	{
		return Super::MoveTo(MoveRequest, OutPath);
	}		

	FPathFollowingRequestResult Result;
	
	Result.Code = EPathFollowingRequestResult::Failed;
	
	return Result;

}

