// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/ClipBox.h"
#include "PlayerCharacter.h"
#include "ItemBox/ItemBoxSpawner.h"

void AClipBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	if (Character)
	{
		if (!Character->IsFullClip())
		{
			Character->IncreasePlayerClip(Clip);
			if (Spawner)
				Spawner->DestroyBox();
		}
	}
}