// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemySpawnPoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SpawnVolume->SetupAttachment(RootComponent);
}

FVector AEnemySpawnPoint::GetSpawnPointInVolume()
{
	FVector randomPoint = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), SpawnVolume->GetScaledBoxExtent());
	randomPoint.Z = SpawnVolume->GetComponentLocation().Z;
	return randomPoint;
}