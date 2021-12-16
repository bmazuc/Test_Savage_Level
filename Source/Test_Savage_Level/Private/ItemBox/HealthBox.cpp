// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/HealthBox.h"
#include "PlayerCharacter.h"
#include "ItemBox/ItemBoxSpawner.h"

void AHealthBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	if (Character)
	{
		if (!Character->IsFullHealth())
		{
			Character->Heal(Health);
			if (Spawner)
				Spawner->DestroyBox();
		}
	}
}
