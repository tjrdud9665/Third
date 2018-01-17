// Fill out your copyright notice in the Description page of Project Settings.

#include "PointComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties

UPointComponent::UPointComponent(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bAutoActivate = true;
	// ...
}

//void UPointComponent::Server_SetPoint_Implementation(EPointType PointType, float _newPoint)
//{
//	FPointInfo* MyPoint = Points.Find(PointType);
//
//	MyPoint->CurrentValue = UKismetMathLibrary::Clamp(_newPoint, 0, MyPoint->MaxValue);
//}
//
//bool UPointComponent::Server_SetPoint_Validate(EPointType PointType, float _newPoint)
//{
//	return true;
//}


// Called when the game starts
void UPointComponent::BeginPlay()
{
	Super::BeginPlay();

	
	for (auto& Elem: Points)
	{
		Elem.Value.CurrentValue = Elem.Value.MaxValue;
	}
	
	// ...
	
}


// Called every frame
void UPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPointComponent::SetPoint(EPointType PointType, float _newPoint)
{
	FPointInfo* MyPoint = Points.Find(PointType);

	MyPoint->CurrentValue = UKismetMathLibrary::Clamp(_newPoint, 0, MyPoint->MaxValue);
}


