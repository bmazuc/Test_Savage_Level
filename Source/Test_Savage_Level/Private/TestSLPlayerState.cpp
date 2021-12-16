// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSLPlayerState.h"

void ATestSLPlayerState::UpdateScore(int points)
{
	SetScore(GetScore() + points);
}

bool ATestSLPlayerState::UpdateHighScore()
{
	if (HighScore < GetScore())
	{
		HighScore = GetScore();
		return true;
	}

	return false;
}