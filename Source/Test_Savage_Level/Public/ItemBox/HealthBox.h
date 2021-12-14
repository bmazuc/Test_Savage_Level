// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBox/ItemBox.h"
#include "HealthBox.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API AHealthBox : public AItemBox
{
	GENERATED_BODY()
	
public:
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int Health = 10;
};
