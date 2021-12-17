// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovement = GetCharacterMovement();
}

void AEnemy::UpdateWalkSpeed(float WalkSpeed)
{
	CharacterMovement->MaxWalkSpeed = WalkSpeed;
}