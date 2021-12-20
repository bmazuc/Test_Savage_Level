// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyDeath.h"
#include "CharacterWithHealth.h"

void UAnimNotifyDeath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacterWithHealth* CharacterWithHealth = Cast<ACharacterWithHealth>(MeshComp->GetOwner());

	if (CharacterWithHealth)
		CharacterWithHealth->FinishDeathAnim();
}