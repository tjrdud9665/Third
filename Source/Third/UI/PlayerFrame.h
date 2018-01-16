// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SType.h"
#include "PlayerFrame.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API UPlayerFrame : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* GauageContainer;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Gauage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGauage> GaugeWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Gauage" , meta = (AllowPrivateAccess = "true"))
	TArray<class UGauage*> GauageWidgets;
	
public:
	UFUNCTION()
	void CreatePointGauage(EPointType ExpressPointType);
	//void Client_CreatePointGauage_Implementation(EPointType ExpressPointType);

	UFUNCTION()
	void SetGauagePercent(EPointType ExpressPointType,FPointInfo _Point);




	
	
};
