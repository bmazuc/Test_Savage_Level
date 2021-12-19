// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovement = GetCharacterMovement();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	FAttachmentTransformRules attachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true
	);
	Weapon->AttachToComponent(GetMesh(), attachmentTransformRules, WeaponSocket);
	FRotator newRotation = Weapon->GetActorRotation();
	newRotation.Yaw = GetActorRotation().Yaw;
	Weapon->SetActorRotation(newRotation);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShootTimer > 0.f)
	{
		ShootTimer -= DeltaTime;
	}
}

void AEnemy::UpdateWalkSpeed(float WalkSpeed)
{
	CharacterMovement->MaxWalkSpeed = WalkSpeed;
}

void AEnemy::FireShoot()
{
	if (ShootTimer > 0.f)
		return;

	Aim();

	if (Weapon)
	{
		Weapon->Shoot(GetActorForwardVector());
		ShootTimer = Weapon->GetFireRate();
	}
}

void AEnemy::Aim()
{
	FRotator newRotation = Weapon->GetActorRotation();
	newRotation.Yaw = GetActorRotation().Yaw;
	Weapon->SetActorRotation(newRotation);
}