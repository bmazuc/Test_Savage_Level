// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreSave.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API UScoreSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	int GetHighScore() { return HighScore; }
	void SetHighScore(int NewHighScore) { HighScore = NewHighScore; }

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int HighScore;
};
