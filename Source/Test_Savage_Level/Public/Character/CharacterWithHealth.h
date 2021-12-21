// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterWithHealth.generated.h"

UCLASS()
class TEST_SAVAGE_LEVEL_API ACharacterWithHealth : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterWithHealth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Heal(int Health);
	bool IsFullHealth();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool IsDead();
	virtual void Die();
	virtual void FinishDeathAnim();

protected:
	void StartInvincibility();

private:
	void StopInvincibility();

protected:
	UPROPERTY(Category = Score, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int DeathScoreModifier;

	UPROPERTY(Category = Invincibility, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", AllowPrivateAccess = "true"))
	float InvincibilityTime = 5.f;
	bool bInvincible;
	FTimerHandle InvincibilityTimerHandle;

	UPROPERTY(Category = Health, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int MaxHealth = 100;
	UPROPERTY(Category = Health, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurrentHealth;

	bool bIsDead = false;
};
