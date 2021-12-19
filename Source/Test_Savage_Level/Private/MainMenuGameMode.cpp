// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "GameFramework/PlayerController.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
		PlayerController->bShowMouseCursor = true;

	if (!WidgetClass)
		return;

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	if (widget)
	{
		if (widget->bIsFocusable && PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(widget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
		}
		widget->AddToViewport();
	}
}