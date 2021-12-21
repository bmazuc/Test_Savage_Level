// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestSLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API ATestSLPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	void PauseGame();
};
