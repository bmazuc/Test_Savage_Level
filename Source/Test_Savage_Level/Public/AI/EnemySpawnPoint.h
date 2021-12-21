// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class UBoxComponent;

#include "EnemySpawnPoint.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();
	FVector GetSpawnPointInVolume();

private:
	UPROPERTY(Category = ItemBox, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnVolume;
};
