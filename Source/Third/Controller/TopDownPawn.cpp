// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownPawn.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Controller/CustomPlayerController.h"

// Sets default values
ATopDownPawn::ATopDownPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//> Create Components
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	RootScene = CreateDefaultSubobject<USceneComponent>("Root");


	//> Setup Hierichy Struct..
	RootComponent = RootScene;
	CameraBoom->SetupAttachment(RootScene);
	TopDownCamera->SetupAttachment(CameraBoom);


}



// Called when the game starts or when spawned
void ATopDownPawn::BeginPlay()
{
	Super::BeginPlay();

	//Server_Initialize();

	
}

// Called every frame
void ATopDownPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATopDownPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

