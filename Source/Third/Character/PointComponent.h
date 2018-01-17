// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SType.h"
#include "PointComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRD_API UPointComponent : public UActorComponent
{
	GENERATED_BODY()

private:
/////////////////////////     Point       ///////////////////////////
//> This Valiable is Only Set in Server
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	TMap<EPointType, struct FPointInfo> Points;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	struct FStatInfo StatInfo;






public:	
	// Sets default values for this component's properties
	UPointComponent(const class FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

public:
	UFUNCTION()
		void SetPoint(EPointType PointType, float _newPoint);

	FORCEINLINE TArray<EPointType> GetPointType()
	{
		TArray<EPointType> PointTypes;
		Points.GetKeys(PointTypes);

		return PointTypes;
	}
		
	FORCEINLINE const FPointInfo* GetPoint(EPointType PointType)
	{
		return Points.Find(PointType);
	}
	
};
