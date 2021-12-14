// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSLGameMode.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

void ATestSLGameMode::Respawn(AController* playerController)
{
	if (!playerController)
		return;

	AActor* start = FindPlayerStart(playerController);

	if (!start)
		return;

	RestartPlayerAtPlayerStart(playerController, start);
}

void ATestSLGameMode::Quit()
{
	//UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit);
}