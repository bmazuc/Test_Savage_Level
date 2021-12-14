// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyDeath.h"
#include "PlayerCharacter.h"

void UAnimNotifyDeath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (PlayerCharacter)
		PlayerCharacter->FinishDeathAnim();
}