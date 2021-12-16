// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterWithHealth.h"
#include "Weapon.h"

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

	void TempTakeDamage();
	void Die() override;

	AWeapon* GetWeapon() { return Weapon; }

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
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(Category = PlayerCharacter, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName WeaponSocket;

	UPROPERTY(Category = PlayerCharacter, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AWeapon* Weapon;

	EPlayerCharacterState CurrentState = EPlayerCharacterState::IdleRun;
	bool bIsShooting = false;

	APlayerController* PlayerController;
};
