// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SType.h"
#include "Gauage.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API UGauage : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GauageValueText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* GauageBar;

	UPROPERTY()
	EPointType GauagePointType;

	UPROPERTY()
	struct FPointInfo PointInfo;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TMap< EPointType,FLinearColor > GauageColorMap;
	
	
public:
	UFUNCTION()
	void InitializeProgressBar(EPointType _GauagePointType);

	UFUNCTION()
	void SetGauagePercent(FPointInfo _Point);

	
	FORCEINLINE EPointType GetExpressPointType()
	{
		return GauagePointType;
	}




	
protected:
	virtual void NativeConstruct() override;

};
