// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile.h"

class UCharacterMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class APlayerController;

#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	IdleRun,
	Aim,
	Reload,
	Dead
};

UCLASS()
class APlayerCharacter : public ACharacter
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

	UPROPERTY(Category = "PlayerCharacter|Weapon", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float gunOffset = 85.f;

	float ShootTimer;

	UPROPERTY(Category = "PlayerCharacter|Weapon", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int MaxAmmo = 50;
	UPROPERTY(Category = "PlayerCharacter|Weapon", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ClipAmmo;

	UPROPERTY(Category = "PlayerCharacter|Weapon", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int MaxClip = 9;
	UPROPERTY(Category = "PlayerCharacter|Weapon", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ClipCount;

	UPROPERTY(Category = "PlayerCharacter|Weapon", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float FireRate = 0.24f;

	EPlayerCharacterState CurrentState = EPlayerCharacterState::IdleRun;
	bool bIsShooting = false;

	APlayerController* PlayerController;

	UPROPERTY(Category = PlayerCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;
};
