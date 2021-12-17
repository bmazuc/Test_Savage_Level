// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWithHealth.h"

class UCharacterMovementComponent;

#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API AEnemy : public ACharacterWithHealth
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AEnemy();

	void UpdateWalkSpeed(float WalkSpeed);

private:
	UCharacterMovementComponent* CharacterMovement;
};
