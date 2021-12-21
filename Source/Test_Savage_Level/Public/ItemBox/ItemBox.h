// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class AItemBoxSpawner;
class UBoxComponent;
class UStaticMeshComponent;

#include "ItemBox.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBox();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) PURE_VIRTUAL(AItemBox::OnBeginOverlap, ;);

	void SetSpawner(AItemBoxSpawner* NewSpawner);

protected:
	AItemBoxSpawner* Spawner;
	UPROPERTY(Category = ItemBox, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Collider;
	UPROPERTY(Category = ItemBox, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoxMesh;
};
