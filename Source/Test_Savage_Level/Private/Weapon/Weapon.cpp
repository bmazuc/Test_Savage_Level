// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Components/SceneComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	ClipAmmo = MaxAmmo;
	ClipCount = MaxClip;
	CurrentSpread = 0.f;
}

void AWeapon::UpdateSpread(float DeltaTime)
{
	CurrentSpread = FMath::Max(MinSpread, CurrentSpread - WeaponSpreadRecoveryRate * DeltaTime);
}

void AWeapon::IncreaseClip(int Clip)
{
	ClipCount = FMath::Min(MaxClip, ClipCount + Clip);
}

bool AWeapon::IsFullClip()
{
	return (ClipCount >= MaxClip);
}

bool AWeapon::HasNoClip()
{
	return (ClipCount <= 0);
}

bool AWeapon::IsFullAmmo()
{
	return (ClipAmmo >= MaxAmmo);
}

bool AWeapon::IsClipEmpty()
{
	return (ClipAmmo <= 0);
}

void AWeapon::Reload()
{
	--ClipCount;
	ClipAmmo = MaxAmmo;
}

void AWeapon::Shoot()
{
	if (!bHasUnlimitedAmmo)
		--ClipAmmo;

	FVector lookDir = GetActorForwardVector();

	if (CurrentSpread > 0.f)
	{
		float zAxis = lookDir.Z;
		lookDir = UKismetMathLibrary::RandomUnitVectorInConeInRadians(lookDir, FMath::DegreesToRadians(CurrentSpread * .5f));
		lookDir.Z = zAxis;
	}

	FVector location = WeaponMesh->GetSocketLocation(ShootSocketName);
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, location, lookDir.Rotation());
	projectile->SetDamage(Damages);

	//Add spread.
	CurrentSpread = FMath::Min(MaxSpread, CurrentSpread + WeaponSpreadPerShot);
}