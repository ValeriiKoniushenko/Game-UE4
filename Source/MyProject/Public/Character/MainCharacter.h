// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainAttributeSet.h"
#include "MainCharacter.generated.h"

class UAbilitySystemComponent;
class UCameraComponent;
class UMainAttributeSet;
class UMainCharacterMovementComponent;
class UMainMovementComponent;
class USpringArmComponent;
class UAnimMontage;

UCLASS()
class MYPROJECT_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainCharacter(const FObjectInitializer& ObjectInitializer);
	virtual ~AMainCharacter() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	UMainAttributeSet* MainAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	TSubclassOf<UGameplayAbility> CrouchAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	UAnimMontage* CrouchAnimMontage;
	
	UFUNCTION(BlueprintCallable)
	bool IsWantToRun() const;

	UFUNCTION(BlueprintCallable)
	bool IsWantToJog() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsWantToWalk() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsIdle() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsWantToIdle() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsWantToStop() const;
	
	UFUNCTION(BlueprintCallable)
	void AbilityToAcquire();

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

private:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Offset);
	void MoveRight(float Offset);
	void MoveCrouch();
	void RequestWalk(float);
	void RequestRun(float);
	UMainCharacterMovementComponent* GetCustomMovementComponent() const;

private:
	bool bIsWantToRun = false;
	bool bIsWantToJog = false;
	bool bIsWantToWalk = false;
};
