// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFrame.h"
#include "Character/PointComponent.h"
#include "UI/Gauage.h"
#include "Components/VerticalBox.h"
#include "UI/UIFactory.h"


void UPlayerFrame::CreatePointGauage(EPointType ExpressPointType)
{
	UGauage* Gauage =  UIFactory::CreateGauage<UGauage>(GetOwningPlayer(), GaugeWidgetClass.Get(),ExpressPointType);	
	
	GauageContainer->AddChildToVerticalBox(Gauage);

	GauageWidgets.Add(Gauage);

}

void UPlayerFrame::SetGauagePercent(EPointType ExpressPointType, FPointInfo _Point)
{
	for (UGauage* Gauage : GauageWidgets)
	{
		if (Gauage->GetExpressPointType() == ExpressPointType)
		{
			Gauage->SetGauagePercent(_Point);
			return;
		}		
	}
}

