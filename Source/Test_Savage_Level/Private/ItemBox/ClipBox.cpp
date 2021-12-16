// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox/ClipBox.h"
#include "PlayerCharacter.h"
#include "ItemBox/ItemBoxSpawner.h"

void AClipBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	if (!Character)
		return;

	AWeapon* weapon = Character->GetWeapon();

	if (!weapon)
		return;

	if (!weapon->IsFullClip())
	{
		weapon->IncreaseClip(Clip);
		if (Spawner)
			Spawner->DestroyBox();
	}
}