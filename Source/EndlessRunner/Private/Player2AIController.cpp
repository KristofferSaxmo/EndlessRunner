// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2AIController.h"
#include "MyPawn.h"
#include "EndlessRunner/EndlessRunnerGameModeBase.h"
#include "Kismet/GameplayStatics.h"

class AMyPlatform;

void APlayer2AIController::BeginPlay()
{
	Super::BeginPlay();
	CurrentPlatform = &(Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->TailPlatform);
}

void APlayer2AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = Cast<AMyPawn>(InPawn);
}

void APlayer2AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Timer += DeltaSeconds;
	const AMyPlatform* TargetPlatform = *CurrentPlatform;
	if (FreeLanes != TargetPlatform->NextPlatform->FreeLanes)
	{
		FindDesiredPosition(TargetPlatform);
	}

	if (ControlledPawn->Position == DesiredPosition) return;

	if (FMath::Abs(ControlledPawn->Position - DesiredPosition) > 1)
		ControlledPawn->Jump();
	
	if (Timer < MoveCooldown) return;
	
	ControlledPawn->Position > DesiredPosition ? ControlledPawn->Move(true) : ControlledPawn->Move(false);
	Timer = 0.0f;
}

void APlayer2AIController::FindDesiredPosition(const AMyPlatform* TargetPlatform)
{
	FreeLanes = TargetPlatform->NextPlatform->FreeLanes;
	if (FreeLanes.Num() == 0)
	{
		FindDesiredPosition(TargetPlatform->NextPlatform);
	}
	else
	{
		DesiredPosition = FindClosestFreeLane();
	}
}

int32 APlayer2AIController::FindClosestFreeLane() const
{
	const int32 CurrentPosition = ControlledPawn->Position;
	int32 ClosestValue = FreeLanes[0];
	int32 MinDifference = FMath::Abs(ClosestValue - CurrentPosition);

	for (const int32 Val : FreeLanes)
	{
		const int32 CurrentDifference = FMath::Abs(Val - CurrentPosition);
		if (CurrentDifference < MinDifference)
		{
			MinDifference = CurrentDifference;
			ClosestValue = Val;
		}
	}

	return ClosestValue;
}
