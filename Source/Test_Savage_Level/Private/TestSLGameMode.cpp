// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSLGameMode.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

void ATestSLGameMode::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &ATestSLGameMode::EndGame, GameDuration, false);
	PlayerController = GetWorld()->GetFirstPlayerController();

	if (PauseWidgetClass)
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
}

void ATestSLGameMode::Respawn(AController* playerController)
{
	if (!playerController)
		return;

	AActor* start = FindPlayerStart(playerController);

	if (!start)
		return;

	RestartPlayerAtPlayerStart(playerController, start);
}

void ATestSLGameMode::PauseGame(bool bPause)
{
	if (!PlayerController)
		return;

	if (bPause)
	{
		if (PauseWidget->bIsFocusable)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(PauseWidget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
		}
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	PlayerController->bShowMouseCursor = bPause;

	if (PauseWidget)
	{
		if (bPause)
			PauseWidget->AddToViewport();
		else
			PauseWidget->RemoveFromViewport();
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
		UUserWidget* EndWidget = CreateWidget<UUserWidget>(GetWorld(), EndWidgetClass);

		if (EndWidget->bIsFocusable)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(EndWidget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
		}

		EndWidget->AddToViewport();
	}

	PlayerController->SetPause(true);
}

void ATestSLGameMode::Quit()
{
	//UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit);
}