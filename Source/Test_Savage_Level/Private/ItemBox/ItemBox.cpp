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

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent >(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	if (!Collider->OnComponentBeginOverlap.IsAlreadyBound(this, &AItemBox::OnBeginOverlap))
		Collider->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnBeginOverlap);
}

void AItemBox::SetSpawner(AItemBoxSpawner* NewSpawner)
{
	Spawner = NewSpawner;
}