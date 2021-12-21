// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "Camera/CameraComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "TestSLGameMode.h"
#include "TestSLPlayerState.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovement = GetCharacterMovement();
	if (CharacterMovement)
	{
		CharacterMovement->bUseControllerDesiredRotation = true;
		CharacterMovement->bOrientRotationToMovement = true;
	}
	bUseControllerRotationYaw = false;

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 900.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	// Create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CrosshairMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crosshair"));
	CrosshairMesh->SetupAttachment(RootComponent);
	CrosshairMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	if (CharacterMovement)
		RunSpeed = CharacterMovement->MaxWalkSpeed;

	ShootTimer = 0.f;

	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	FAttachmentTransformRules attachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		true
		);
	Weapon->AttachToComponent(GetMesh(), attachmentTransformRules, WeaponSocket);

	FRotator newRotation = Weapon->GetActorRotation();
	newRotation.Yaw = PlayerController->GetControlRotation().Yaw;
	Weapon->SetActorRotation(newRotation);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Weapon)
		Weapon->UpdateSpread(DeltaTime);

	if (CurrentState == EPlayerCharacterState::Aim)
	{
		AimToCursor(DeltaTime);
		if (IsShooting())
		{
			ShootTimer += DeltaTime;
			if (ShootTimer > Weapon->GetFireRate())
			{
				ShootTimer = 0.f;
				FireShoot();
			}
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	InputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartAim);
	InputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &APlayerCharacter::EndAim);

	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerCharacter::StartShoot);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &APlayerCharacter::EndShoot);

	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &APlayerCharacter::Reload);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (CurrentState == EPlayerCharacterState::Dead)
		return;

	// Use Forward Vector because we want to move independently of the rotation as it is a top-down shooter.
	AddMovementInput(Value * FVector::ForwardVector);
}

void APlayerCharacter::MoveRight(float Value)
{
	if (CurrentState == EPlayerCharacterState::Dead)
		return;

	// Use Right Vector because we want to move independently of the rotation as it is a top-down shooter.
	AddMovementInput(Value * FVector::RightVector);
}

void APlayerCharacter::StartAim()
{
	if (CurrentState != EPlayerCharacterState::IdleRun)
		return;

	CurrentState = EPlayerCharacterState::Aim;

	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = AimSpeed;
		CharacterMovement->bOrientRotationToMovement = false;
	}

	CrosshairMesh->SetVisibility(true);

	bUseControllerRotationYaw = true;
}

void APlayerCharacter::EndAim()
{
	if (CurrentState == EPlayerCharacterState::Reload || CurrentState == EPlayerCharacterState::Dead)
		return;

	bIsShooting = false;

	CurrentState = EPlayerCharacterState::IdleRun;

	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = RunSpeed;
		CharacterMovement->bOrientRotationToMovement = true;
	}

	CrosshairMesh->SetVisibility(false);

	PlayerController->SetControlRotation(FRotator());
	bUseControllerRotationYaw = false;
}

EPlayerCharacterState APlayerCharacter::GetCurrentState()
{
	return CurrentState;
}

bool APlayerCharacter::IsShooting()
{
	return bIsShooting;
}

void APlayerCharacter::StartShoot()
{
	if (CurrentState == EPlayerCharacterState::Aim)
	{
		bIsShooting = true;
		if (Weapon)
			ShootTimer = Weapon->GetFireRate();
	}
}

void APlayerCharacter::EndShoot()
{
	if (CurrentState == EPlayerCharacterState::Reload || CurrentState == EPlayerCharacterState::Dead)
		return;

	bIsShooting = false;
}

void APlayerCharacter::FireShoot()
{
	if (!Weapon)
		return;

	if (Weapon->IsClipEmpty())
		EndShoot();
	else
		Weapon->Shoot();
}

void APlayerCharacter::AimToCursor(float DeltaTime)
{
	if (!PlayerController)
		return;

	FHitResult hitResult;
	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, hitResult))
	{
		FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitResult.Location);
		FRotator newControlRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), lookAt, DeltaTime, 33);
		PlayerController->SetControlRotation(newControlRotation);

		if (Weapon)
		{
			FRotator newRotation = Weapon->GetActorRotation();
			newRotation.Yaw = PlayerController->GetControlRotation().Yaw;
			Weapon->SetActorRotation(newRotation);
		}
		CrosshairMesh->SetWorldLocation(hitResult.Location + hitResult.ImpactNormal * 10.f);
	}
}

void APlayerCharacter::Reload()
{
	if (!Weapon)
		return;

	if (CurrentState == EPlayerCharacterState::Reload || Weapon->IsFullAmmo() || Weapon->HasNoClip()
		|| CurrentState == EPlayerCharacterState::Dead)
		return;

	if (bIsShooting)
		EndShoot();

	if (CurrentState == EPlayerCharacterState::Aim)
		EndAim();

	CurrentState = EPlayerCharacterState::Reload;
	CharacterMovement->MaxWalkSpeed = ReloadWalkSpeed;
}

void APlayerCharacter::EndReload()
{
	if (CurrentState != EPlayerCharacterState::Reload || !Weapon)
		return;

	Weapon->Reload();
	CurrentState = EPlayerCharacterState::IdleRun;
	CharacterMovement->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::Die()
{
	Super::Die();

	CurrentState = EPlayerCharacterState::Dead;
}

void APlayerCharacter::FinishDeathAnim()
{
	if (Weapon)
		Weapon->Destroy();

	Destroy();

	ATestSLGameMode* gameMode = Cast<ATestSLGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode && PlayerController)
		gameMode->Respawn(PlayerController);
}