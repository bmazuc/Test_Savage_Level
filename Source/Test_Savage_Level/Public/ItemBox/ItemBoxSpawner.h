// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.h"
#include "ItemBoxSpawner.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API AItemBoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void DestroyBox();

private:
	void SpawnBox();

	AItemBox* Box;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(Category = ItemBoxSpawner, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AItemBox> ItemBoxClass;

	UPROPERTY(Category = ItemBoxSpawner, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpawnTimer = 5.f;
};
