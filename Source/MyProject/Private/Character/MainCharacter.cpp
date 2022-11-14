// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/MainCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainCharacter, All, All);

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UMainCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	check(SpringArmComponent);
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	UMainCharacterMovementComponent* MovementComponent = GetCustomMovementComponent();
	check(MovementComponent);
	MovementComponent->TopJogSpeed = 400.f;
	MovementComponent->TopWalkSpeed = 150.f;
	MovementComponent->TopRunSpeed = 800.f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	check(CameraComponent);
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SpringArmComponent"));
}

bool AMainCharacter::IsWantToRun() const
{
	return bIsWantToRun && !bIsWantToWalk && bIsWantToJog;
}

bool AMainCharacter::IsWantToJog() const
{
	return !bIsWantToRun && !bIsWantToWalk && bIsWantToJog;
}

bool AMainCharacter::IsWantToWalk() const
{
	return !bIsWantToRun && bIsWantToWalk && bIsWantToJog;
}

bool AMainCharacter::IsIdle() const
{
	return FMath::IsNearlyZero(GetVelocity().Size());
}

bool AMainCharacter::IsWantToIdle() const
{
	return !bIsWantToJog && !bIsWantToWalk && !bIsWantToRun;
}

bool AMainCharacter::IsWantToStop() const
{
	static float LastSpeed = 0;
	
	const bool Result = IsWantToIdle() && (GetVelocity().Size() < LastSpeed);

	LastSpeed = GetVelocity().Size();
	
	return Result;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);

	PlayerInputComponent->BindAxis("TurnAround", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("SlowWalking", this, &AMainCharacter::RequestWalk);
	PlayerInputComponent->BindAxis("Run", this, &AMainCharacter::RequestRun);
}

void AMainCharacter::MoveForward(float Value)
{
	bIsWantToJog = Value > 0.f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::RequestWalk(float Value)
{
	bIsWantToWalk = !FMath::IsNearlyZero(Value);
	
	if (auto* MovementComponent = GetCustomMovementComponent())
	{
		if (!bIsWantToRun)
		{
			MovementComponent->SetWalkingMode(IsWantToWalk() ? EWalkingMode::Walk : EWalkingMode::Jog);
		}
	}
}

void AMainCharacter::RequestRun(float Value)
{
	bIsWantToRun = !FMath::IsNearlyZero(Value);

	if (auto* MovementComponent = GetCustomMovementComponent())
	{
		if (!bIsWantToWalk)
		{
			MovementComponent->SetWalkingMode(IsWantToRun() ? EWalkingMode::Run : EWalkingMode::Jog);
		}
	}
}

UMainCharacterMovementComponent* AMainCharacter::GetCustomMovementComponent() const
{
	auto* MovementComponent = Cast<UMainCharacterMovementComponent>(GetMovementComponent());
	if (!MovementComponent)
		UE_LOG(LogMainCharacter, Error, TEXT("Impossible to get Main Character Movement Component"));

	return MovementComponent;
}