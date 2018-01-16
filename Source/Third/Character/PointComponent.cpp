// Fill out your copyright notice in the Description page of Project Settings.

#include "PointComponent.h"


// Sets default values for this component's properties
UPointComponent::UPointComponent(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


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

