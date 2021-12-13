// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacter.h"
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
	UPROPERTY(Category = PlayerCharacter, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(Category = PlayerCharacter, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Direction;

	UPROPERTY(Category = PlayerCharacter, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsAiming;

	APlayerCharacter* PlayerCharacter;
};
