// Fill out your copyright notice in the Description page of Project Settings.

#include "MelleAttackNotifyState.h"
#include "Character/BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interface/CombatInterface.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"




void UMelleAttackNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (!MeshComp)
		return;

	UWorld* World = GetWorld();


	if (!(MeshComp->GetOwnerRole() < ROLE_Authority))
	{
		OwnerCharacter = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (!OwnerCharacter)
			return;

		OwnerCharacter->GetWorldTimerManager().SetTimer(HitTraceTimer, this, &UMelleAttackNotifyState::GenerateLineTrace, 0.1f, true);

	}


}

void UMelleAttackNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	//>Editor Guard
	if (!MeshComp)
		return;

	UWorld* World = GetWorld();


	if (!OwnerCharacter)
	{
		return;
	}

	//Run Only Server..
	if (!(MeshComp->GetOwnerRole() < ROLE_Authority))
	{
		if (OwnerCharacter->GetWorldTimerManager().TimerExists(HitTraceTimer))
		{
			DamagedActor.Empty();
			OwnerCharacter->GetWorldTimerManager().ClearTimer(HitTraceTimer);
		}
		
	}

	
}

void UMelleAttackNotifyState::GenerateLineTrace()
{
	if (!OwnerCharacter)
		return;

	FVector StartPos = OwnerCharacter->GetActorLocation();// +UKismetMathLibrary::Conv_RotatorToVector(OwnerCharacter->GetActorRotation());

	FVector EndPos = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * ICombatInterface::Execute_GetAttackRange(OwnerCharacter);

	//Collision Channel
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryObj;
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery1);
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery2);
	QueryObj.Add(EObjectTypeQuery::ObjectTypeQuery3);

	TArray<AActor*> IgnoreList;

	TArray<FHitResult> HitReults;

	auto Result = UKismetSystemLibrary::CapsuleTraceMultiForObjects(OwnerCharacter, StartPos, EndPos,34, 88, QueryObj, true, IgnoreList, EDrawDebugTrace::Persistent, HitReults, true);

	if (Result)
	{
		for (auto Hit : HitReults)
		{
			if (!DamagedActor.Contains(Hit.Actor))
			{				
				Hit.Actor->TakeDamage(ICombatInterface::Execute_GetAttackDamage(OwnerCharacter), FDamageEvent(),OwnerCharacter->GetController() ,OwnerCharacter);
				DamagedActor.Add(Hit.GetActor());
				//UGameplayStatics::ApplyDamage()
			}
		}
	}

}
