// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainAttributeSet.h"
#include "Components/MainCharacterMovementComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY_STATIC(LogMainCharacter, All, All);

AMainCharacter::AMainCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UMainCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	MainAttributeSet = CreateDefaultSubobject<UMainAttributeSet>(TEXT("MainAttributeSet"));
	check(MainAttributeSet);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	check(AbilitySystemComponent);
	
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
	CameraComponent->SetupAttachment(SpringArmComponent);
}

AMainCharacter::~AMainCharacter()
{
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

void AMainCharacter::AbilityToAcquire()
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && CrouchAbility)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(CrouchAbility, 1, 0));
		}
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->RefreshAbilityActorInfo();
}

void AMainCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilityToAcquire();
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

	PlayerInputComponent->BindAxis("TurnAround", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("SlowWalking", this, &AMainCharacter::RequestWalk);
	PlayerInputComponent->BindAxis("Run", this, &AMainCharacter::RequestRun);
	
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::MoveCrouch);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
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

void AMainCharacter::MoveCrouch()
{
	AbilitySystemComponent->TryActivateAbilityByClass(CrouchAbility);
	// PlayAnimMontage(CrouchAnimMontage);
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