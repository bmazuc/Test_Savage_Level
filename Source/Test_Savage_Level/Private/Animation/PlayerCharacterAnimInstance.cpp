// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacterAnimInstance.h"
#include "Animation/AnimationsUtilities.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	JogDeathIdx = FMath::RandRange(0, JogDeathMaxRange);
	AimDeathIdx = FMath::RandRange(0, AimDeathMaxRange);
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!PlayerCharacter)
		return;

	FVector velocity = PlayerCharacter->GetVelocity();
	FRotator playerRotation = PlayerCharacter->GetActorRotation();

	Speed = velocity.Size();
	Direction = CalculateDirection(velocity, playerRotation);
	PlayerCharacterState = PlayerCharacter->GetCurrentState();

	UAnimationsUtilities::UpdateMontagePlayState(this, ReloadMontage, PlayerCharacterState == EPlayerCharacterState::Reload);
	UAnimationsUtilities::UpdateMontagePlayState(this, FireMontage, PlayerCharacter->IsShooting());
}