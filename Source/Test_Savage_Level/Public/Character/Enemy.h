// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterWithHealth.h"
#include "Weapon/Weapon.h"

class UCharacterMovementComponent;
class AEnemyDirector;

#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API AEnemy : public ACharacterWithHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateWalkSpeed(float WalkSpeed);
	void FireShoot();
	bool ConsumeShootTrigger();

	void SetDirector(AEnemyDirector* NewDirector);

	virtual void Die() override;
	virtual void FinishDeathAnim() override;

private:
	void Aim();

private:
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(Category = "Enemy|Weapon", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(Category = "Enemy|Weapon", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName WeaponSocket;

	UPROPERTY(Category = "Enemy|Weapon", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AWeapon* Weapon;

	float ShootTimer = 0.f;

	bool bHasShoot;

	AEnemyDirector* Director;
};
