// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestSLGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API ATestSLGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void Respawn(AController* playerController);
	void Quit();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* PlayerStart;
};
