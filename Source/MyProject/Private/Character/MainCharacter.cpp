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

bool AMainCharacter::IsWantToRun() const
{
	return bIsWantToRun;
}

bool AMainCharacter::IsWantToSlowWalk() const
{
	return bIsWantToSlowWalk;
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

	PlayerInputComponent->BindAxis("SlowWalking", this, &AMainCharacter::RequestSlowWalk);
	PlayerInputComponent->BindAxis("Run", this, &AMainCharacter::RequestRun);
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::RequestSlowWalk(float Value)
{
	bIsWantToSlowWalk = !FMath::IsNearlyZero(Value);
	
	auto* MovementComponent = Cast<UMainCharacterMovementComponent>(GetMovementComponent());
	if (!bIsWantToRun)
		MovementComponent->SetWalkingMode(bIsWantToSlowWalk ? EWalkingMode::SlowWalk : EWalkingMode::Walk);
}

void AMainCharacter::RequestRun(float Value)
{
	bIsWantToRun = !FMath::IsNearlyZero(Value);

	auto* MovementComponent = Cast<UMainCharacterMovementComponent>(GetMovementComponent());
	if (!bIsWantToSlowWalk)
		MovementComponent->SetWalkingMode(bIsWantToRun ? EWalkingMode::Run : EWalkingMode::Walk);
}
