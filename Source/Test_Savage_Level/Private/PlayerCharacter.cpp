// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovement = GetCharacterMovement();
	if (CharacterMovement)
		CharacterMovement->bOrientRotationToMovement = true;

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
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	if (CharacterMovement)
		RunSpeed = CharacterMovement->MaxWalkSpeed;

	ShootTimer = 0.f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAiming())
	{
		AimToCursor(DeltaTime);
		if (IsShooting())
		{
			ShootTimer += DeltaTime;
			if (ShootTimer > FireRate)
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
}

void APlayerCharacter::MoveForward(float Value)
{
	FRotator rotator = GetControlRotation();
	rotator.Pitch = 0.f;
	rotator.Roll = 0.f;
	AddMovementInput(Value * rotator.Vector());
}

void APlayerCharacter::MoveRight(float Value)
{
	FRotator rotator = GetControlRotation();
	rotator.Pitch = 0.f;
	rotator.Roll = 0.f;
	AddMovementInput(Value * rotator.RotateVector(FVector::RightVector));
}

void APlayerCharacter::StartAim()
{
	bIsAiming = true;

	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = AimSpeed;
		CharacterMovement->bOrientRotationToMovement = false;
	}

	if (PlayerController)
		PlayerController->bShowMouseCursor = true;

	bUseControllerRotationYaw = true;
}

void APlayerCharacter::EndAim()
{
	bIsAiming = false;
	bIsShooting = false;

	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = RunSpeed;
		CharacterMovement->bOrientRotationToMovement = true;
	}

	if (PlayerController)
		PlayerController->bShowMouseCursor = false;

	bUseControllerRotationYaw = false;
}

bool APlayerCharacter::IsAiming()
{
	return bIsAiming;
}

bool APlayerCharacter::IsShooting()
{
	return bIsShooting;
}

void APlayerCharacter::StartShoot()
{
	if (IsAiming())
	{
		bIsShooting = true;
		ShootTimer = FireRate;
	}
}

void APlayerCharacter::EndShoot()
{
	bIsShooting = false;
}

void APlayerCharacter::FireShoot()
{
	FRotator rotator = GetControlRotation();
	rotator.Pitch = 0.f;
	rotator.Roll = 0.f;
	FVector location = GetActorLocation() + rotator.Vector() * gunOffset;
	GetWorld()->SpawnActor(ProjectileClass, &location, &rotator);
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
	}
}