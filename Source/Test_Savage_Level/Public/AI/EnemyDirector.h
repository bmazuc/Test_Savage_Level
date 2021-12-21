// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Enemy.h"
#include "AI/EnemySpawnPoint.h"
#include "EnemyDirector.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API AEnemyDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	void DecreaseCurrentEnemyCount();

private:
	void CompleteEnemyHorde();
	void SpawnEnemy();

	UPROPERTY(Category = EnemyDirector, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxEnemyCount = 10;

	int CurrentEnemyCount = 0;

	UPROPERTY(Category = EnemyDirector, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(Category = EnemyDirector, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AEnemySpawnPoint*> SpawnPoints;

	UPROPERTY(Category = EnemyDirectorEditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.1f, AllowPrivateAccess = "true"))
	float SecondPerCompletion = 5.f;

	FTimerHandle CompletionTimerHandle;
};
