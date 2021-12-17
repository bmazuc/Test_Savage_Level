// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!EnemyCharacter)
		return;

	FVector velocity = EnemyCharacter->GetVelocity();

	Speed = velocity.Size();
}