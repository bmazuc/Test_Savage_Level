// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "GameFramework/PlayerController.h"

void AMainMenuGameMode::BeginPlay()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
		PlayerController->bShowMouseCursor = true;

	if (!WidgetClass)
		return;

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	if (widget)
		widget->AddToViewport();


}