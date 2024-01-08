// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Player1Controller.generated.h"


/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API APlayer1Controller : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;
};