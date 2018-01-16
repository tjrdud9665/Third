// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SType.h"
/**
 * 
 */
class THIRD_API UIFactory
{
public:
	//template<typename T>
	//static T* CreateStatGauage(UClass* Class, EUnitStatType StatType, class AFirstPlayerController* Controller);

	//template<typename T>
	//static T* CreatePlayerFrame(UClass* Class, class AFirstPlayerController* Controller);

	template<typename T>
	static T* CreateHUD(class APlayerController* _Controller ,UClass* Class);

	template<typename T>
	static T* CreatePlayerFrame(class APlayerController* _Controller , UClass* Class, TArray<EPointType> ExpressPointType);

	template<typename T>
	static T* CreateGauage(class APlayerController* _Controller, UClass* Class , EPointType _PointType );


};

template<typename T>
T* UIFactory::CreateHUD(class APlayerController* _Controller, UClass* Class )
{
	T* HUD = CreateWidget<T>(_Controller, Class);


	return HUD;
}

template<typename T>
T* UIFactory::CreatePlayerFrame(class APlayerController* _Controller, UClass* Class, TArray<EPointType> ExpressPointType)
{
	T* Result = CreateWidget<T>(_Controller, Class);

	
	for (auto PointType : ExpressPointType)
	{
		Result->CreatePointGauage(PointType);
	}
	
	

	return Result;
	
}

template<typename T>
T* UIFactory::CreateGauage(class APlayerController* _Controller, UClass* Class, EPointType _PointType)
{
	T* Gauage = CreateWidget<T>(_Controller, Class);

	Gauage->InitializeProgressBar(_PointType);

	return Gauage;


}
