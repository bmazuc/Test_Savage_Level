// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

class UAnimInstance;
class UAnimMontage;

#include "AnimationsUtilities.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API UAnimationsUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Animation)
	static void UpdateMontagePlayState(UAnimInstance* target, UAnimMontage* Montage, bool ShouldPlay, float InPlayRate = 1.f, float OutBlendTime = .5f);
};
