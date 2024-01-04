// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "MyPawn.h"
#include "MyPlatform.h"

#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	if (Timer > 1)
	{
		Timer -= 1;
		Score += Velocity;
		PlayerHUD->UpdateScore(Score);
		Velocity += Acceleration;
		for (AMyPlatform* Platform : Platforms)
		{
			Platform->Velocity = Velocity;
		}
	}
	
	if (TailPlatform->GetActorLocation().X > 0)
	{
		PlatformPool.Dequeue(HeadPlatform);
		HeadPlatform->DeleteObstacles();
		PlatformPool.Enqueue(HeadPlatform);
		PlatformPool.Peek(TailPlatform);
		const FVector Location(-100 * (Amount), 0.0f, 0.0f);
		HeadPlatform->SetActorLocation(Location);

		Counter++;
		if (Counter != PlatformsPerObstacle) return;
		Counter = 0;
		HeadPlatform->SpawnObstacles();
	}
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnInitialPlatforms();

	PlayerHUD = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHudClass);
	PlayerHUD->AddToViewport();

	PlayersAlive = GetNumPlayers();
}

void AEndlessRunnerGameModeBase::ReportDeadPlayer()
{
	PlayersAlive--;
	if (PlayersAlive == 0)
	{
		const FString FilePath = FPaths::ProjectDir() + TEXT("Highscore.txt");
		FString HighscoreStr;
		FFileHelper::LoadFileToString(HighscoreStr, *FilePath);

		int32 HighscoreInt = FCString::Atoi(*HighscoreStr);

		if (Score > HighscoreInt)
		{
			FFileHelper::SaveStringToFile(FString::FromInt(Score), *FilePath);
		}
		
		UGameplayStatics::OpenLevel(this, FName("MenuLevel"), false);
	}
}

void AEndlessRunnerGameModeBase::SpawnInitialPlatforms()
{
	UWorld* World = GetWorld();
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < Amount; i++)
	{
		const FActorSpawnParameters SpawnInfo;
		FVector Location(-100 * i, 0.0f, 0.0f);
		AMyPlatform* Platform = World->SpawnActor<AMyPlatform>(PlatformClass, Location, Rotation, SpawnInfo);
		PlatformPool.Enqueue(Platform);
		Platforms.Add(Platform);
		Platform->Velocity = Velocity;

		if (i > 2)
		{
			Counter++;
			if (Counter == PlatformsPerObstacle)
			{
				Counter = 0;
				Platform->SpawnObstacles();
			}
		}
	}
	PlatformPool.Peek(TailPlatform);
}

