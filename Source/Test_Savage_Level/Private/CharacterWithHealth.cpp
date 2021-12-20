// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWithHealth.h"
#include "TestSLPlayerState.h"

// Sets default values
ACharacterWithHealth::ACharacterWithHealth()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterWithHealth::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	StartInvincibility();
}

// Called every frame
void ACharacterWithHealth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterWithHealth::Heal(int health)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + health);
}

bool ACharacterWithHealth::IsFullHealth()
{
	return (CurrentHealth >= MaxHealth);
}

float ACharacterWithHealth::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (bInvincible || bIsDead)
		return 0.f;

	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0)
		Die();

	return DamageAmount;
}

bool ACharacterWithHealth::IsDead()
{
	return bIsDead;
}

void ACharacterWithHealth::Die()
{
	bIsDead = true;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		ATestSLPlayerState* playerState = PlayerController->GetPlayerState<ATestSLPlayerState>();
		if (playerState)
			playerState->UpdateScore(DeathScoreModifier);
	}
}

void ACharacterWithHealth::StartInvincibility()
{
	bInvincible = true;

	GetWorld()->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &ACharacterWithHealth::StopInvincibility, InvincibilityTime, false);
}

void ACharacterWithHealth::StopInvincibility()
{
	bInvincible = false;
}

void ACharacterWithHealth::FinishDeathAnim()
{

}