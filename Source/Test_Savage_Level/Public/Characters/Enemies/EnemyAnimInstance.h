// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/Enemies/Enemy.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Speed;
	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;
	UPROPERTY(Category = PlayerCharacterAnimInstance, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int DeathIdx;
	UPROPERTY(Category = PlayerCharacterAnimInstance, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int DeathMaxRange = 2;
	AEnemy* EnemyCharacter;

	UPROPERTY(Category = "Resources|Montages", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireMontage;
};
