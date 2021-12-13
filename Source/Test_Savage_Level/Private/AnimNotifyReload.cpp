// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyReload.h"
#include "PlayerCharacter.h"

void UAnimNotifyReload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (PlayerCharacter)
		PlayerCharacter->EndReload();
}