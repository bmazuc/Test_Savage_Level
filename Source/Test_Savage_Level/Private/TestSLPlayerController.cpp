// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSLPlayerController.h"
#include "TestSLGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"

void ATestSLPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
}

void ATestSLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &ATestSLPlayerController::PauseGame);
}

void ATestSLPlayerController::PauseGame()
{
	ATestSLGameMode* gameMode = Cast<ATestSLGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (gameMode)
		gameMode->PauseGame(true);
}