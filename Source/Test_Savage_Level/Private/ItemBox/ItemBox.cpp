// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/ItemBox.h"
#include "ItemBox/ItemBoxSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = collider;
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent >(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	if (!collider->OnComponentBeginOverlap.IsAlreadyBound(this, &AItemBox::OnBeginOverlap))
		collider->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnBeginOverlap);
}

void AItemBox::SetSpawner(AItemBoxSpawner* newSpawner)
{
	Spawner = newSpawner;
}