// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyPawn.h"
#include "MyPlatform.h"
#include "Player2AIController.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API APlayer2AIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	void FindDesiredPosition(const AMyPlatform* TargetPlatform);
	int32 FindClosestFreeLane() const;
	
	AMyPlatform** CurrentPlatform;
	AMyPawn* ControlledPawn;
	TArray<int32> FreeLanes;
	int32 DesiredPosition;
	float MoveCooldown = 0.15f;
	float Timer;
};
