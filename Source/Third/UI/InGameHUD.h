// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SType.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRD_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* PlayerFrameContainer;

	UPROPERTY()
	class UPlayerFrame* PlayerFrame;

	UPROPERTY()
	TArray<class UPlayerFrame*> PartyPlayerFrames;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerFrame> PlayerFrameClass;

public:
	//Must call In Authority
	UFUNCTION()
	void CreatePlayerFrame(class APlayerController* _OwningPlayer ,const TArray<EPointType>& ExpressPointType );

	UFUNCTION()
	void CreatePartyPlayerFrame(class APlayerController* _OwningPlayer, const TArray<EPointType>& ExpressPointType);

	UFUNCTION()
		class UPlayerFrame*  GetPlayerFrame();

	UFUNCTION()
	TArray<class UPlayerFrame* > GetPartyPlayerFrames();


private:
	UFUNCTION()
	void AddPlayerFrame(class UPlayerFrame* _PlayerFrame);

	UFUNCTION()
	void AddPartyPlayerFrame(class UPlayerFrame* _PlayerFrame);
	





	
	
	
};
