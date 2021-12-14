// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/ItemBoxSpawner.h"

// Sets default values
AItemBoxSpawner::AItemBoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	box = nullptr;
}

// Called when the game starts or when spawned
void AItemBoxSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnBox();
}

void AItemBoxSpawner::DestroyBox()
{
	if (!box)
		return;

	box->Destroy();
	box = nullptr;

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemBoxSpawner::SpawnBox, SpawnTimer, false);
}

void AItemBoxSpawner::SpawnBox()
{
	if (box)
		return;

	box = GetWorld()->SpawnActor<AItemBox>(ItemBoxClass, GetActorLocation(), GetActorRotation());

	if (box)
		box->SetSpawner(this);
}

