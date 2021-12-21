// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner());
	bIsDead = false;
	DeathIdx = FMath::RandRange(0, DeathMaxRange);
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!EnemyCharacter)
		return;

	FVector velocity = EnemyCharacter->GetVelocity();
	Speed = velocity.Size();

	bIsDead = EnemyCharacter->IsDead();

	if (EnemyCharacter->ConsumeShootTrigger())
		Montage_Play(FireMontage);
}