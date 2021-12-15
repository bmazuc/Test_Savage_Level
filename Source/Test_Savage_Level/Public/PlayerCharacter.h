// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterWithHealth.h"
#include "Projectile.h"

class UCharacterMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class APlayerController;

#include "PlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gunOffset = 85.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 0.24f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Damages = 10;

// Clip and ammo datas

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int MaxAmmo = 50;
	UPROPERTY(BlueprintReadWrite)
	int ClipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int MaxClip = 9;
	UPROPERTY(BlueprintReadWrite)
	int ClipCount;

// SpreadData

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinSpread = 2.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxSpread = 30.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WeaponSpreadPerShot = 4.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WeaponSpreadRecoveryRate = 1.5f;

	UPROPERTY(Transient, BlueprintReadOnly)
	float CurrentSpread;
};

UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	IdleRun,
	Aim,
	Reload,
	Dead
};

UCLASS()
class APlayerCharacter : public ACharacterWithHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsShooting();
	EPlayerCharacterState GetCurrentState();

	void EndReload();
	void FinishDeathAnim();

	// Return false if clip is already maxed.
	void IncreasePlayerClip(int clip);
	bool IsFullClip();

	void TempTakeDamage();
	void Die() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartAim();
	void EndAim();

	void StartShoot();
	void EndShoot();

	void FireShoot();

	void AimToCursor(float DeltaTime);

	void Reload();

private:
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(Category = PlayerCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(Category = PlayerCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(Category = PlayerCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ReloadWalkSpeed = 400.f;
	UPROPERTY(Category = PlayerCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AimSpeed = 300.f;
	float RunSpeed;

	float ShootTimer;

	UPROPERTY(Category = PlayerCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;

	EPlayerCharacterState CurrentState = EPlayerCharacterState::IdleRun;
	bool bIsShooting = false;

	APlayerController* PlayerController;
};
