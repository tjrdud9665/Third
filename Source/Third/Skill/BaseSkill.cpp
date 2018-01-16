// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSkill.h"


void ABaseSkill::OnTrySpellCast_Implementation()
{

}

void ABaseSkill::InitializeSpellCast_Implementation()
{

}

void ABaseSkill::OnSpellCast_Implementation()
{

}

void ABaseSkill::OnCastComplete_Implementation()
{

}

void ABaseSkill::OnCoolDownExpired_Implementation()
{

}

// Sets default values
ABaseSkill::ABaseSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

