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
	
public:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	void PauseGame();
};
