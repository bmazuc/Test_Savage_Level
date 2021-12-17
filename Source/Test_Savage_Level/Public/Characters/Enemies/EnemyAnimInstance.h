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

	AEnemy* EnemyCharacter;
};
