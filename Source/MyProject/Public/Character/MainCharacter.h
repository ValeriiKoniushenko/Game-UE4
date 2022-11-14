// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class UMainMovementComponent;
class UMainCharacterMovementComponent;
class USpringArmComponent;

UCLASS()
class MYPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components")
	USpringArmComponent* SpringArmComponent;

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
	
protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Offset);
	void MoveRight(float Offset);
	void RequestWalk(float);
	void RequestRun(float);
	UMainCharacterMovementComponent* GetCustomMovementComponent() const;

private:
	bool bIsWantToRun = false;
	bool bIsWantToJog = false;
	bool bIsWantToWalk = false;
};
