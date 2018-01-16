// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauage.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"






void UGauage::InitializeProgressBar(EPointType _GauagePointType)
{
	GauagePointType = _GauagePointType;

}



void UGauage::SetGauagePercent(FPointInfo _Point)
{
	if (_Point.MaxValue)
	{
		float Percent = _Point.CurrentValue / _Point.MaxValue;
		GauageBar->SetPercent(Percent);
		auto str = FString::Printf(TEXT("%d / %d"), (int32)_Point.CurrentValue, (int32)_Point.MaxValue);
		GauageValueText->SetText(FText::FromString(str));

	}

}

void UGauage::NativeConstruct()
{
	auto GauageColor = GauageColorMap.Find(GauagePointType);
	if (GauageColor)
	{
		GauageBar->SetFillColorAndOpacity(*GauageColor);
	}
	



}

