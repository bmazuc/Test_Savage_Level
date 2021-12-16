// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TestSLPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API ATestSLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void UpdateScore(int points);
	// Return true if highscore have changed.
	bool UpdateHighScore();

	void SetHighScore(int NewScore) { HighScore = NewScore; }
	int GetHighScore() { return HighScore; }

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int HighScore;
};
