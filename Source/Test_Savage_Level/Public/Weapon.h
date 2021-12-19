// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

class USceneComponent;

#include "Projectile.h"

class USkeletalMeshComponent;

#include "Weapon.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Shoot(FVector forward);
	void UpdateSpread(float DeltaTime);
	bool IsFullClip();
	bool IsClipEmpty();
	bool IsFullAmmo();
	void Reload();

	void IncreaseClip(int clip);

	float GetFireRate() { return FireRate; }

private:
	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName ShootSocketName;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireRate = 0.24f;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int Damages = 10;

	// Clip and ammo datas

	UPROPERTY(Category = "Weapon|Ammunitions", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	bool bHasUnlimitedAmmo = false;

	UPROPERTY(Category = "Weapon|Ammunitions", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
		int MaxAmmo = 50;
	UPROPERTY(Category = "Weapon|Ammunitions", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int ClipAmmo;

	UPROPERTY(Category = "Weapon|Ammunitions", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
		int MaxClip = 9;
	UPROPERTY(Category = "Weapon|Ammunitions", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int ClipCount;

	// SpreadData

	UPROPERTY(Category = "Weapon|Spread", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float MinSpread = 2.f;

	UPROPERTY(Category = "Weapon|Spread", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float MaxSpread = 15.f;

	UPROPERTY(Category = "Weapon|Spread", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float WeaponSpreadPerShot = 4.f;

	UPROPERTY(Category = "Weapon|Spread", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float WeaponSpreadRecoveryRate = 1.5f;

	UPROPERTY(Category = "Weapon|Spread", Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float CurrentSpread;
};
