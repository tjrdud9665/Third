// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Character/PointComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


bool ABaseCharacter::BeginFocus_Implementation()
{
	return true;
}

bool ABaseCharacter::EndFocus_Implementation()
{
	return true;
}

float ABaseCharacter::GetUseDistance_Implementation()
{
	return UseDistance;
}

bool ABaseCharacter::GetIsUsable_Implementation()
{
	return bUsable;
}

bool ABaseCharacter::OnUsed_Implementation(class APlayerController* Controller)
{
	return true;
}

float ABaseCharacter::GetTargetDistance(AActor* Target)
{
	if (!Target)
		return 0;

	return (Target->GetActorLocation() - GetActorLocation()).Size();

}

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PointComp = CreateDefaultSubobject<UPointComponent>(TEXT("StatCopomponent"));
	//PointComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	bAlive = true;
	bAttacking = false;
	UseDistance = 128.0f;
	bUsable = true;

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	

}

