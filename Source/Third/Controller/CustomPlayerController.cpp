// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/BaseCharacter.h"
#include "Controller/TopDownPawn.h"
#include "Controller/CustomAIController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Interface/InteractableInterface.h"
#include "Interface/CombatInterface.h"

#include "UI/InGameHUD.h"
#include "UI/UIFactory.h"
#include "UI/PlayerFrame.h"

#include "Kismet/GameplayStatics.h"
#include "PlayGameModeBase.h"

#include "Character/PointComponent.h"
#include "SType.h"

#define SPHERE_TRACE_RAD 16
#define FRAME_UPDATE_INTERVAL 0.1f




ACustomPlayerController::ACustomPlayerController(const class FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bPlayerDead = false;
}

void ACustomPlayerController::Server_InitPlayer_Implementation()
{
	auto ControlledPawn = GetPawn();

	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("RespawnFailed : ControlledPawn is NULL"));
		return;
	}

	TopDownPawn = Cast<ATopDownPawn>(ControlledPawn);

	if (!TopDownPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("RespawnFailed : TopDownPawn Casting Error"));
		return;
	}
		

	RespawnPlayer();

	Client_InitializeHUD();


}

bool ACustomPlayerController::Server_InitPlayer_Validate()
{
	return true;
}

void ACustomPlayerController::OnMousePressed()
{
	if (!bMovementLocked)
	{

		if (bInplaceLock)
		{
			//>Attack or Inplace Action..
		}
		else
		{
			//ClickProcess
			Server_UpdateMouseClick(MouseLocation);			
			
		}

	}	
}

void ACustomPlayerController::Server_Update_Implementation()
{
	if (CurrentTarget && bMovingToTarget)
	{
		float Distance = PlayerCharacter->GetTargetDistance(CurrentTarget);
		//인터페이스 구현 여부
		/*auto Interactable = Cast<IInteractableInterface>(CurrentTarget);
		if (Interactable)
		{
		UsableDistance = Interactable->Execute_GetUseDistance(CurrentTarget);
		}*/
		float UsableDistance = IInteractableInterface::Execute_GetUseDistance(CurrentTarget);

		if (Distance <= UsableDistance)
		{
			UseTargetActor(CurrentTarget);
			bMovingToTarget = false;

		}

	}


}

bool ACustomPlayerController::Server_Update_Validate()
{
	return true;
}

void ACustomPlayerController::Server_UpdateMouseClick_Implementation(FVector Location)
{
	AActor* UsableActor = nullptr;
	GetUsableActor(Location, OUT UsableActor);

	if (UsableActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction!!"));
		//InterfaceCall..
		InteractWithActor(UsableActor);
	}
	else
	{
		//MoveDistance Check.
		float MoveDistance = (PlayerCharacter->GetActorLocation() - MouseLocation).Size();

		if (MoveDistance >= MinMoveDistance)
		{
			//Move!!
			MoveToLocation(Location);
			ShowMouseClick();
		}
	}

}

bool ACustomPlayerController::Server_UpdateMouseClick_Validate(FVector Location)
{
	return true;
}

void ACustomPlayerController::GetUsableActor(const FVector Location, AActor*& OutActor)
{
	//>								Sphere Trace From Camera Location to (Mouse)Location
	if (!TopDownPawn)
	{		
		return;
	}

	FVector CameraLoc = TopDownPawn->GetTopDownCamera()->GetComponentLocation();
	FRotator CameraRot = TopDownPawn->GetTopDownCamera()->GetComponentRotation();

	FVector TraceStart = CameraLoc + UKismetMathLibrary::Conv_RotatorToVector(CameraRot);
	FVector TraceEnd = Location;

	TArray<FHitResult> Hits;
	TArray<AActor*> IgnoreList;
	IgnoreList.Add(PlayerCharacter);
	//>Trace Method 1	

	UKismetSystemLibrary::SphereTraceMulti(this,
		TraceStart,
		TraceEnd,
		SPHERE_TRACE_RAD,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		IgnoreList,
		EDrawDebugTrace::None,
		OUT Hits,
		true);

	//>Trace Method 2
	//GetWorld()->LineTraceMultiByChannel


	int32 LastIdx = Hits.Num() - 1;


	TSubclassOf<UInteractableInterface> Interface;
	if (Hits.IsValidIndex(LastIdx))
	{
		if(Cast<IInteractableInterface>(Hits[LastIdx].GetActor()))
		{			
			OutActor = Hits[LastIdx].GetActor();
		}
	}

}

void ACustomPlayerController::UpdateFollowCamera(float DeltaTime)
{
	if (!TopDownPawn)
		return;
	FVector StartLoc = TopDownPawn->GetActorLocation();
	FVector TargetLoc = PlayerCharacter->GetActorLocation();

	FVector LerpedLoc = UKismetMathLibrary::VInterpTo(StartLoc, TargetLoc, DeltaTime, CameraInterpSpeed);

	TopDownPawn->SetActorLocation(LerpedLoc);
}

void ACustomPlayerController::FocusUpdate()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, OUT Hit);

	if (Hit.bBlockingHit)
	{
		MouseLocation = Hit.Location;
		GetUsableActorFocus(Hit.Location);
	}

}


void ACustomPlayerController::GetUsableActorFocus(FVector Location)
{
	AActor* UsableActor = nullptr;
	GetUsableActor(Location, OUT UsableActor);

	//>새로운것이 포커싱되면 이전 포커스액터를 보내고 새로운것을 포커싱한다고 알림
	if (LastFocusTarget != UsableActor)
	{
		bNewFocus = true;

		if (LastFocusTarget)
			IInteractableInterface::Execute_EndFocus(LastFocusTarget);
		LastFocusTarget = nullptr;
	}
	//>새로운것을 포커싱했다면 LastFocus를 새로운것으로 채우고 플래그를 전환
	if (UsableActor)
	{
		LastFocusTarget = UsableActor;
		if (bNewFocus)
		{
			IInteractableInterface::Execute_BeginFocus(LastFocusTarget);
			bNewFocus = false;

		}
	}
	//>만약 새로 포커싱된 타겟이 사용불가능하다면 포커싱해제
	if (LastFocusTarget)
	{
		//> 사용불가시 포커스 해제
		if (IInteractableInterface::Execute_GetIsUsable(LastFocusTarget))
		{
			IInteractableInterface::Execute_EndFocus(LastFocusTarget);
		}

	}

}

void ACustomPlayerController::Client_InitializeHUD_Implementation()
{
	if (IsLocalController())
	{
		HudWidget = UIFactory::CreateHUD<UInGameHUD>(this, HUDWidgetClass.Get());

		HudWidget->AddToViewport();

	}
}

void ACustomPlayerController::Client_CreatePlayerFrame_Implementation()
{
	CreatePlayerFrame();
}

void ACustomPlayerController::CreatePlayerFrame()
{

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is not Initializing Fininsh"));
		return;
	}
	if (!PlayerCharacter->GetPointComp())
	{
		UE_LOG(LogTemp, Error, TEXT("Component is not Initializing Fininsh"));
		return;
	}

	HudWidget->CreatePlayerFrame(this, PlayerCharacter->GetPointComp()->GetPointType());
	
	GetWorldTimerManager().ClearTimer(UIInitialTimer);	
	
}

void ACustomPlayerController::Client_UpdatePlayerFrame_Implementation(EPointType PointType, FPointInfo PointInfo)
{
	
	auto Frame = HudWidget->GetPlayerFrame();
	
	if(Frame)
		Frame->SetGauagePercent(PointType, PointInfo);


}

void ACustomPlayerController::Server_UpdatePlayerFrame_Implementation()
{
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter is not Initializing Fininsh"));
		return;
	}

	if (!PlayerCharacter->GetPointComp())
	{
		UE_LOG(LogTemp, Error, TEXT("PointComponent is not Initializing Fininsh"));
		return;
	}

	auto PointComp = PlayerCharacter->GetPointComp();
	auto PointTypes = PointComp->GetPointType();


	for (auto PointType : PointTypes)
	{
		auto Point = PointComp->GetPoint(PointType);

		if(Point)
			Client_UpdatePlayerFrame(PointType, *Point);
	}
}

bool ACustomPlayerController::Server_UpdatePlayerFrame_Validate()
{
	return true;
}

void ACustomPlayerController::Server_UpdatePartyPlayerFrame_Implementation()
{
	TArray<UPointComponent*> PartyCharPointComps;

	for (auto PartPlayer : PartyController)
	{
		auto CastedController = Cast<ACustomPlayerController>(PartPlayer);

		if (CastedController)
		{
			auto PartyChar = CastedController->PlayerCharacter;
			if (PartyChar)
			{
				auto PartyCharPointComp = PartyChar->GetPointComp();
				if(PartyCharPointComp)
					PartyCharPointComps.Add(PartyCharPointComp);
			}			

		}
	}

	for (int32 i = 0; i < PartyController.Num(); i++)
	{
		if (PartyCharPointComps.IsValidIndex(i))
		{
			auto PointTypes = PartyCharPointComps[i]->GetPointType();

			for (auto PointType : PointTypes)
			{			
				auto Point = PartyCharPointComps[i]->GetPoint(PointType);

				if (Point)
				{
					Client_UpdatePartyPlayerFrame(PointType, *Point);
					auto CustomController = Cast<ACustomPlayerController>(PartyController[i]);
					if (CustomController)
					{
						Client_UpdatePartyPlayerFrame(PointType, *Point);
						CustomController->Client_UpdatePartyPlayerFrame(PointType, *Point);
					}
					
				}
			}
		}
	}

}

bool ACustomPlayerController::Server_UpdatePartyPlayerFrame_Validate()
{
	return true;
}

void ACustomPlayerController::Server_AddPartyPlayer_Implementation()
{
	auto GameMode = UGameplayStatics::GetGameMode(this);

	APlayGameModeBase* PlayGameMode = Cast<APlayGameModeBase>(GameMode);

	if (!PlayGameMode)
	{
		return;
	}

	auto PartyPlayerController = PlayGameMode->GetPartyPlayer();

	for (auto PartyMember : PartyPlayerController)
	{
		auto PartyCon = Cast<ACustomPlayerController>(PartyMember);



		if (PartyCon != this)
		{
			if (PartyController.Find(PartyCon) == INDEX_NONE)
			{
				PartyCon->Client_AddPartyFrames(PartyMember, PartyCon->PlayerCharacter);
				Client_AddPartyFrames(PartyMember, PartyCon->PlayerCharacter);
				PartyController.Add(PartyCon);

			}

		}

	}


}

bool ACustomPlayerController::Server_AddPartyPlayer_Validate()
{
	return true;
}

void ACustomPlayerController::Client_AddPartyFrames_Implementation(APlayerController* _OwnPlayer, ABaseCharacter* _PartyCharacter)
{
	AddPartyFrames(_OwnPlayer, _PartyCharacter);
}

void ACustomPlayerController::AddPartyFrames(APlayerController* _OwnPlayer, class ABaseCharacter* _PartyCharacter)
{
	if (!_PartyCharacter)
		return;
	auto PointComp = _PartyCharacter->GetPointComp();
	if (!PointComp)
		return;

	HudWidget->CreatePartyPlayerFrame(this, PointComp->GetPointType());
}

void ACustomPlayerController::Client_UpdatePartyPlayerFrame_Implementation(EPointType PointType, FPointInfo PointInfo)
{
	auto PartyFrames = HudWidget->GetPartyPlayerFrames();

	for (auto PartyFrame : PartyFrames)
	{
		if (PartyFrame)
		{
			PartyFrame->SetGauagePercent(PointType, PointInfo);
		}
	}


}

void ACustomPlayerController::Party()
{
	Server_AddPartyPlayer();

	GetWorld()->GetTimerManager().SetTimer(PartyFrameUpdateTimer, this ,&ACustomPlayerController::Server_UpdatePartyPlayerFrame, FRAME_UPDATE_INTERVAL, true);
	

}

void ACustomPlayerController::RespawnPlayer()
{

	if (!TopDownPawn)
		return;

	TArray<AActor*> PlayerStarts;

	UGameplayStatics::GetAllActorsOfClass(
		this,
		APlayerStart::StaticClass(),
		OUT PlayerStarts);

	int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, PlayerStarts.Num() - 1);

	if (PlayerStarts.IsValidIndex(RandomIndex))
	{
		FVector RespawnLocation = PlayerStarts[RandomIndex]->GetActorLocation();

		TopDownPawn->SetActorLocation(RespawnLocation);

		FActorSpawnParameters SpawnInfo;

		//>>For Playing Spawn Character and AI Con ,TopDownCameraPawn(ForNetworking)..
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PlayerCharacter = GetWorld()->SpawnActor<ABaseCharacter>(CharacterClass, TopDownPawn->GetActorTransform(), SpawnInfo);		

		PlayerCharacter->SetPlayerController(this);

		AiController = GetWorld()->SpawnActor<ACustomAIController>(ACustomAIController::StaticClass(), TopDownPawn->GetActorTransform());

		AiController->Possess(PlayerCharacter);

		this->Possess(TopDownPawn);				
		

	}

	if (Role < ROLE_Authority)
	{
		Server_RespawnPlayer();
	}


}

void ACustomPlayerController::Server_RespawnPlayer_Implementation()
{
	if (bPlayerDead)
	{
		bPlayerDead = false;
		bMovementLocked = false;

		RespawnPlayer();

		Client_RespawnPlayer();

	}
}

bool ACustomPlayerController::Server_RespawnPlayer_Validate()
{
	return true;
}

void ACustomPlayerController::Client_RespawnPlayer_Implementation()
{

}



void ACustomPlayerController::MoveToLocation(FVector Location)
{
	if (AiController)
	{
		AiController->MoveToLocation(Location);
	}
}

void ACustomPlayerController::InteractWithActor(AActor* InteractActor)
{
	if (HasAuthority())
	{
		CurrentTarget = InteractActor;
		bMovingToTarget = false;
		float TargetDistance = PlayerCharacter->GetTargetDistance(CurrentTarget);


		//TODO: Some Interaction Actor with Interact..
		auto TargetCharacter = Cast<ABaseCharacter>(CurrentTarget);

		if (TargetCharacter)
		{
			if (ICombatInterface::Execute_GetIsHostil(TargetCharacter) && ICombatInterface::Execute_GetIsAlive(TargetCharacter))
			{

			}
		}



	}
}

bool ACustomPlayerController::UseTargetActor(AActor* TargetACtor)
{
	if (HasAuthority())
	{
		AiController->StopMovement();
		IInteractableInterface::Execute_OnUsed(TargetACtor, this);
		return true;
	}
	else
		return false;
}

void ACustomPlayerController::ShowMouseClick()
{

}

void ACustomPlayerController::Client_ShowMouseClick_Implementation()
{
	ShowMouseClick();
}



//Engine Function
void ACustomPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateFollowCamera(DeltaTime);

	if (IsLocalController())
	{
		if (!bMovementLocked)
		{
			FocusUpdate();
		}
	}


	Server_Update();
	//ServerUpdate();
}

void ACustomPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACustomPlayerController, bMovementLocked);
	DOREPLIFETIME(ACustomPlayerController, TopDownPawn);
	DOREPLIFETIME(ACustomPlayerController, PlayerCharacter);
	DOREPLIFETIME(ACustomPlayerController, LastFocusTarget);
	DOREPLIFETIME(ACustomPlayerController, AiController);
	


}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		Server_InitPlayer();

		FInputModeGameAndUI InputMode;		
		InputMode.SetHideCursorDuringCapture(false);
		
		SetInputMode(InputMode);
		bShowMouseCursor = true	;			
		
		GetWorld()->GetTimerManager().SetTimer(UIInitialTimer,this, &ACustomPlayerController::Client_CreatePlayerFrame, 0.5f, true);	
		GetWorld()->GetTimerManager().SetTimer(FrameUpdateTimer, this, &ACustomPlayerController::Server_UpdatePlayerFrame , FRAME_UPDATE_INTERVAL, true);		
	}
	


}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ACustomPlayerController::OnMousePressed);

}
