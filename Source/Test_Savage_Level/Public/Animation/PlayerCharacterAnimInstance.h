// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/PlayerCharacter.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 *
 */
UCLASS(Transient, Blueprintable)
class TEST_SAVAGE_LEVEL_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Direction;

	APlayerCharacter* PlayerCharacter;

	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerCharacterState PlayerCharacterState;

	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int JogDeathIdx;

	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int AimDeathIdx;

	UPROPERTY(Category = PlayerCharacterAnimInstance, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int JogDeathMaxRange = 2;

	UPROPERTY(Category = PlayerCharacterAnimInstance, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int AimDeathMaxRange = 1;

	UPROPERTY(Category = "Resources|Montages", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadMontage;

	UPROPERTY(Category = "Resources|Montages", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireMontage;
};
