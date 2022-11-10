// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/MainCharacterMovementComponent.h"

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
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	check(CameraComponent);
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SpringArmComponent"));
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
}

void AMainCharacter::MoveForward(float Offset)
{
	AddMovementInput(GetActorForwardVector(), Offset);
}

void AMainCharacter::MoveRight(float Offset)
{
	AddMovementInput(GetActorRightVector(), Offset);
}
