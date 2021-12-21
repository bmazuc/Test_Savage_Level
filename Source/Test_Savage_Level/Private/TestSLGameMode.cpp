// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSLGameMode.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "ScoreSave.h"
#include "TestSLPlayerState.h"

void ATestSLGameMode::BeginPlay()
{
	Super::BeginPlay();

	TimerManager = &(GetWorld()->GetTimerManager());
	TimerManager->SetTimer(GameTimerHandle, this, &ATestSLGameMode::EndGame, GameDuration, false);
	PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
		PlayerState = PlayerController->GetPlayerState<ATestSLPlayerState>();

	if (PauseWidgetClass)
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);

	if (InGameWidgetClass)
	{
		InGameWidget = CreateWidget<UUserWidget>(GetWorld(), InGameWidgetClass);
		if (InGameWidget)
			InGameWidget->AddToViewport();
	}

	LoadScore();
}

float ATestSLGameMode::GetRemainingTime()
{
	return TimerManager ? TimerManager->GetTimerRemaining(GameTimerHandle) : 0.f;
}

void ATestSLGameMode::Respawn(AController* Controller)
{
	if (!Controller)
		return;

	AActor* start = FindPlayerStart(Controller);

	if (!start)
		return;

	RestartPlayerAtPlayerStart(Controller, start);
}

void ATestSLGameMode::PauseGame(bool bPause)
{
	if (!PlayerController)
		return;

	if (bPause)
	{
		if (PauseWidget->bIsFocusable)
		{
			FInputModeUIOnly inputModeData;
			inputModeData.SetWidgetToFocus(PauseWidget->TakeWidget());
			inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(inputModeData);
		}
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	PlayerController->bShowMouseCursor = bPause;

	if (PauseWidget && InGameWidget)
	{
		if (bPause)
		{
			InGameWidget->RemoveFromViewport();
			PauseWidget->AddToViewport();
		}
		else
		{
			PauseWidget->RemoveFromViewport();
			InGameWidget->AddToViewport();
		}
	}

	PlayerController->SetPause(bPause);
}

void ATestSLGameMode::EndGame()
{
	if (!PlayerController)
		return;

	PlayerController->bShowMouseCursor = true;

	if (EndWidgetClass)
	{
		UUserWidget* endWidget = CreateWidget<UUserWidget>(GetWorld(), EndWidgetClass);

		if (endWidget->bIsFocusable)
		{
			FInputModeUIOnly inputModeData;
			inputModeData.SetWidgetToFocus(endWidget->TakeWidget());
			inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(inputModeData);
		}

		InGameWidget->RemoveFromViewport();
		endWidget->AddToViewport();
	}

	PlayerController->SetPause(true);
	SaveScore();
}

void ATestSLGameMode::LoadScore()
{
	if (UGameplayStatics::DoesSaveGameExist("highscore", 0))
	{
		UScoreSave* scoreSave = Cast<UScoreSave>(UGameplayStatics::LoadGameFromSlot("highscore", 0));
		if (PlayerState)
		{
			PlayerState->SetHighScore(scoreSave->GetHighScore());
		}
	}
	else
	{
		UScoreSave* scoreSave = Cast<UScoreSave>(UGameplayStatics::CreateSaveGameObject(UScoreSave::StaticClass()));
		UGameplayStatics::SaveGameToSlot(scoreSave, "highscore", 0);
	}
}

void ATestSLGameMode::SaveScore()
{
	if (UGameplayStatics::DoesSaveGameExist("highscore", 0))
	{
		UScoreSave* scoreSave = Cast<UScoreSave>(UGameplayStatics::LoadGameFromSlot("highscore", 0));

		if (!PlayerState)
			return;

		if (PlayerState->UpdateHighScore())
		{
			scoreSave->SetHighScore(PlayerState->GetHighScore());

			UGameplayStatics::SaveGameToSlot(scoreSave, "highscore", 0);
		}
	}
}