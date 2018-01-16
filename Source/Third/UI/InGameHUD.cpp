// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "UI/UIFactory.h"
#include "UI/PlayerFrame.h"


void UInGameHUD::CreatePlayerFrame(class APlayerController* _OwningPlayer ,  const TArray< EPointType>& ExpressPointType)
{
	auto Frames = UIFactory::CreatePlayerFrame<UPlayerFrame>(_OwningPlayer, PlayerFrameClass.Get() , ExpressPointType);

	AddPlayerFrame(Frames);
	

}

void UInGameHUD::CreatePartyPlayerFrame(class APlayerController* _OwningPlayer, const TArray<EPointType>& ExpressPointType)
{


	auto Frames = UIFactory::CreatePlayerFrame<UPlayerFrame>(_OwningPlayer, PlayerFrameClass.Get(), ExpressPointType);		
	
	
	PartyPlayerFrames.Add(Frames);	
	AddPartyPlayerFrame(Frames);
	




	
}

class UPlayerFrame* UInGameHUD::GetPlayerFrame()
{
	return PlayerFrame;
}

TArray<class UPlayerFrame* > UInGameHUD::GetPartyPlayerFrames()
{
	return PartyPlayerFrames;

}


void UInGameHUD::AddPlayerFrame(UPlayerFrame* _PlayerFrame)
{
	auto Slot = PlayerFrameContainer->AddChildToUniformGrid(_PlayerFrame);

	PlayerFrame = _PlayerFrame;

	Slot->SetRow(0);
}

void UInGameHUD::AddPartyPlayerFrame(class UPlayerFrame* _PlayerFrame)
{
	auto Slot = PlayerFrameContainer->AddChildToUniformGrid(_PlayerFrame);
	
	Slot->SetRow(PartyPlayerFrames.Num());
}
