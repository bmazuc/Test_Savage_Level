// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "GameFramework/PlayerController.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if (playerController)
		playerController->bShowMouseCursor = true;

	if (!WidgetClass)
		return;

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	if (widget)
	{
		if (widget->bIsFocusable && playerController)
		{
			FInputModeUIOnly inputModeData;
			inputModeData.SetWidgetToFocus(widget->TakeWidget());
			inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			playerController->SetInputMode(inputModeData);
		}
		widget->AddToViewport();
	}
}