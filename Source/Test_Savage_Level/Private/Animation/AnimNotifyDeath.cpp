// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyDeath.h"
#include "Character/CharacterWithHealth.h"

void UAnimNotifyDeath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacterWithHealth* characterWithHealth = Cast<ACharacterWithHealth>(MeshComp->GetOwner());

	if (characterWithHealth)
		characterWithHealth->FinishDeathAnim();
}