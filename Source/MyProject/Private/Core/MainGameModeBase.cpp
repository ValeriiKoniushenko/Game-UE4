// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameModeBase.h"

#include "MainCharacter.h"
#include "MainGameStateBase.h"
#include "MainHUD.h"
#include "MainPlayerController.h"

AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	HUDClass = AMainHUD::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	GameStateClass = AMainPlayerController::StaticClass();
}
