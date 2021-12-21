// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/HealthBox.h"
#include "Character/PlayerCharacter.h"
#include "ItemBox/ItemBoxSpawner.h"

void AHealthBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* character = Cast<APlayerCharacter>(OtherActor);

	if (character)
	{
		if (!character->IsFullHealth())
		{
			character->Heal(Health);
			if (Spawner)
				Spawner->DestroyBox();
		}
	}
}
