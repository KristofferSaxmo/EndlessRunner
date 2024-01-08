// Fill out your copyright notice in the Description page of Project Settings.

#include "Player1Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

class UEnhancedInputLocalPlayerSubsystem;


void APlayer1Controller::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);
}