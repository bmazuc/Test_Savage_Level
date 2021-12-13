// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!PlayerCharacter)
		return;

	FVector velocity = PlayerCharacter->GetVelocity();
	FRotator playerRotation = PlayerCharacter->GetActorRotation();

	Speed = velocity.Size();
	Direction = CalculateDirection(velocity, playerRotation);
	bIsAiming = PlayerCharacter->IsAiming();
}