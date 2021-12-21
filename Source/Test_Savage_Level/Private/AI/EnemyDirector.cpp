// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyDirector.h"

// Sets default values
AEnemyDirector::AEnemyDirector()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyDirector::BeginPlay()
{
	Super::BeginPlay();
	
	CompleteEnemyHorde();

	GetWorld()->GetTimerManager().SetTimer(CompletionTimerHandle, this, &AEnemyDirector::CompleteEnemyHorde, SecondPerCompletion, true);
}

void AEnemyDirector::Destroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(CompletionTimerHandle);
}

void AEnemyDirector::CompleteEnemyHorde()
{
	while (CurrentEnemyCount < MaxEnemyCount)
	{
		SpawnEnemy();
	}
}

void AEnemyDirector::SpawnEnemy()
{
	if (SpawnPoints.Num() == 0)
		return;

	float rand = FMath::FRandRange(0, SpawnPoints.Num() - 1);

	AEnemySpawnPoint* selectedSpawnPoint = SpawnPoints[rand];

	if (!selectedSpawnPoint)
		return;

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AEnemy* enemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, selectedSpawnPoint->GetSpawnPointInVolume(), selectedSpawnPoint->GetActorRotation(), spawnParameters);
	enemy->SetDirector(this);

	++CurrentEnemyCount;
}

void AEnemyDirector::DecreaseCurrentEnemyCount()
{
	--CurrentEnemyCount;
}