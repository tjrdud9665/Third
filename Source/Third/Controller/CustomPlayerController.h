// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SType.h"
#include "CustomPlayerController.generated.h"


/*Engine Game Cycle******************************************************/
/*GameInstance->Level,GameMode->Controller->Pawn->Character             */
/************************************************************************/




/*
*	Tip
	서버 함수가 아닌데 서버에서만 사용되어야 하는함수는 함수 전문에 HasAuthority함수를 이용해서 오쏘리티 채크를 해주면 크러쉬를 줄일수있다.
*/





/**
 * 
 */
UCLASS()
class THIRD_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACustomPlayerController(const class FObjectInitializer& ObjectInitializer);

	//For Controlling  and  Managing Character..
private:
	UPROPERTY(Replicated)
	class ABaseCharacter* PlayerCharacter;

	UPROPERTY(Replicated)
	class ATopDownPawn* TopDownPawn;

	UPROPERTY(Replicated)
	class ACustomAIController* AiController;

	UPROPERTY(EditAnywhere, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseCharacter> CharacterClass;


/////////////////////////     State       ///////////////////////////
	UPROPERTY()
	uint32 bPlayerDead : 1;


////////////////////////     Input      //////////////////////////////////
	UPROPERTY(BlueprintReadOnly ,Replicated , Category = "Input", meta = (AllowPrivateAccess = "true"))
	uint32 bMovementLocked : 1;

	UPROPERTY(BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	uint32 bInplaceLock : 1;

	UPROPERTY()
	uint32 bMovingToTarget : 1;

	UPROPERTY()
	FVector MouseLocation;

	UPROPERTY()
	uint32 bMoveToTarget : 1;

	UPROPERTY()
	AActor* CurrentTarget;

	UPROPERTY(Replicated)
	AActor* LastFocusTarget;

	UPROPERTY()
	uint32 bNewFocus : 1;


/////////////////   For BlueprintCustomize   /////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float CameraInterpSpeed =12.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MinMoveDistance = 100.0f;



/////////////////   For InGame UI Widget   /////////////////////////////
	UPROPERTY()
	class UInGameHUD* HudWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UInGameHUD> HUDWidgetClass;

	UPROPERTY()
	FTimerHandle UIInitialTimer;

	UPROPERTY()
	FTimerHandle FrameUpdateTimer;
	/////////////////   For PartySystem   /////////////////////////////
	UPROPERTY()
	TArray<APlayerController*> PartyController;

	UPROPERTY()
	FTimerHandle PartyFrameUpdateTimer;
	
	


	

public:
	//////////////////////////////////////////////////////////////////////////
	//>								For Initializing..
	//>	Call in BeginPlay
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_InitPlayer();
	void Server_InitPlayer_Implementation();
	bool Server_InitPlayer_Validate();

public:
	//////////////////////////////////////////////////////////////////////////	
	//>								For Input Binding..
	UFUNCTION()
	void OnMousePressed();
	//////////////////////////////////////////////////////////////////////////
	//>								Update in Server
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Update();
	void Server_Update_Implementation();
	bool Server_Update_Validate();

	UFUNCTION(Server, Reliable , WithValidation)
	void Server_UpdateMouseClick(FVector Location);
	void Server_UpdateMouseClick_Implementation(FVector Location);
	bool Server_UpdateMouseClick_Validate(FVector Location);

	UFUNCTION()
	void GetUsableActor(const FVector Location , AActor*& OutActor);
	//////////////////////////////////////////////////////////////////////////
	//>								Update in Client(미구현)
	UFUNCTION()
	void UpdateFollowCamera(float DeltaTime);

	UFUNCTION()
	void FocusUpdate();

	UFUNCTION()
	void GetUsableActorFocus(FVector Location);
	//////////////////////////////////////////////////////////////////////////
	//>								UI in Client
	UFUNCTION(Client, Reliable)
	void Client_InitializeHUD();
	void Client_InitializeHUD_Implementation();


	UFUNCTION(Client, Reliable)
	void Client_CreatePlayerFrame();
	void Client_CreatePlayerFrame_Implementation();

	UFUNCTION()
	void CreatePlayerFrame();

	UFUNCTION(Client, Reliable)
	void Client_UpdatePlayerFrame(EPointType PointType, FPointInfo PointInfo);
	void Client_UpdatePlayerFrame_Implementation(EPointType PointType, FPointInfo PointInfo);

	//////////////////////////////////////////////////////////////////////////
	//>								For PartySystem
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddPartyPlayer();
	void Server_AddPartyPlayer_Implementation();
	bool Server_AddPartyPlayer_Validate();

	UFUNCTION(Client, Reliable)
	void Client_AddPartyFrames(APlayerController* _OwnPlayer, class ABaseCharacter* _PartyCharacter);
	void Client_AddPartyFrames_Implementation(APlayerController* _OwnPlayer, class ABaseCharacter* _PartyCharacter);

	UFUNCTION()
	void AddPartyFrames(APlayerController* _OwnPlayer, class ABaseCharacter* _PartyCharacter);

	UFUNCTION(Client, Reliable)
	void Client_UpdatePartyPlayerFrame(EPointType PointType, FPointInfo PointInfo);
	void Client_UpdatePartyPlayerFrame_Implementation(EPointType PointType, FPointInfo PointInfo);

	UFUNCTION(Exec)
	void Party();



	//////////////////////////////////////////////////////////////////////////
	//>								UI in Server
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdatePlayerFrame();
	void Server_UpdatePlayerFrame_Implementation();
	bool Server_UpdatePlayerFrame_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdatePartyPlayerFrame();
	void Server_UpdatePartyPlayerFrame_Implementation();
	bool Server_UpdatePartyPlayerFrame_Validate();



	



	//////////////////////////////////////////////////////////////////////////
	//>								For Respawn..
	UFUNCTION()
	void RespawnPlayer();
	//>In Server..
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RespawnPlayer();
	void Server_RespawnPlayer_Implementation();
	bool Server_RespawnPlayer_Validate();
	//< In Client..
	UFUNCTION(Client, Reliable)
	void Client_RespawnPlayer();
	void Client_RespawnPlayer_Implementation();
	//////////////////////////////////////////////////////////////////////////
	//>								For Movement
	UFUNCTION()
	void MoveToLocation(FVector Location);
	//////////////////////////////////////////////////////////////////////////
	//>								For Interact(Action)(미구현)
	UFUNCTION()
	void InteractWithActor(AActor* InteractActor);
	UFUNCTION()
	bool UseTargetActor(AActor* TargetACtor);

	//////////////////////////////////////////////////////////////////////////
	//>								For Decoration (미구현)
	UFUNCTION()
	void ShowMouseClick();

	UFUNCTION(Client ,Reliable)
	void Client_ShowMouseClick();
	void Client_ShowMouseClick_Implementation();





	
public:
	virtual void PlayerTick(float DeltaTime) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;


	virtual void SetupInputComponent() override;

};
