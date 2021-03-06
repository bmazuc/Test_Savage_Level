// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set class default value. Can be modified in blueprint after.
	InitialLifeSpan = 3.f;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent >(TEXT("ProjectileMesh"));
	ProjectileMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AProjectile::SetDamage(int NewDamage)
{
	Damage = NewDamage;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FPointDamageEvent damageEvent = FPointDamageEvent(10.f, Hit, GetActorForwardVector(), UDamageType::StaticClass());
	OtherActor->TakeDamage(Damage, damageEvent, nullptr, this);
	Destroy();
}