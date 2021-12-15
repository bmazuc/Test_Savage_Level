// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
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

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void PauseGame(bool bPause);

	UFUNCTION(BlueprintCallable)
	float GetRemainingTime();

private:
	void EndGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* PlayerStart;

	FTimerHandle GameTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float GameDuration = 60.f;

	UPROPERTY(Category = UI, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> EndWidgetClass;

	APlayerController* PlayerController;

	UPROPERTY(Category = UI, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	UUserWidget* PauseWidget;

	UPROPERTY(Category = UI, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InGameWidgetClass;

	UPROPERTY()
	UUserWidget* InGameWidget;

	FTimerManager* TimerManager;
};
