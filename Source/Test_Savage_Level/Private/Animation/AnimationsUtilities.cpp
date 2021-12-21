// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimationsUtilities.h"
#include "Animation/AnimInstance.h"

void UAnimationsUtilities::UpdateMontagePlayState(UAnimInstance* Target, UAnimMontage* Montage, bool ShouldPlay, float InPlayRate, float OutBlendTime)
{
	if (ShouldPlay)
	{
		if (!Target->Montage_IsPlaying(Montage))
			Target->Montage_Play(Montage, InPlayRate);
	}
	else
	{
		if (Target->Montage_IsPlaying(Montage))
			Target->Montage_Stop(OutBlendTime, Montage);
	}
}