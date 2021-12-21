// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyReload.h"
#include "Character/PlayerCharacter.h"

void UAnimNotifyReload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (playerCharacter)
		playerCharacter->EndReload();
}