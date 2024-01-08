// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"

#include "MyGameInstance.h"
#include "MyPawn.h"
#include "MyPlatform.h"
#include "Player1Controller.h"
#include "Player2AIController.h"
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
		int32 Count = HeadPlatform->DeleteObstacles();
		bIsCoop ? Count *= 2 : Count;
		for (int32 i = 0; i < Count * 2; i++)
		{
			if (FMath::RandRange(0, 99) < 5)
			{
				// :P
				TailPlatform->NextPlatform->NextPlatform->NextPlatform->NextPlatform->NextPlatform->NextPlatform->DeleteObstacle();
			}
		}
		PlatformPool.Enqueue(HeadPlatform);
		PlatformPool.Peek(TailPlatform);
		const FVector Location(-200 * (Amount), 0.0f, 0.0f);
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

	const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	Lanes = GameInstance->GetLanes();
	bIsCoop = GameInstance->GetIsCoop();
	
	SpawnInitialPlatforms();

	PlayerHUD = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHudClass);
	PlayerHUD->AddToViewport();
	
	const FActorSpawnParameters SpawnInfo;
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	
	if (APlayer1Controller* Player1Controller = Cast<APlayer1Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player 1 controller found"));
		AMyPawn* Player1Pawn = GetWorld()->SpawnActor<AMyPawn>(PlayerClass, FVector(-200.0f, 60.0f, 21.0f), Rotation, SpawnInfo);
		Player1Pawn->Position = -1;
		Player1Controller->Possess(Player1Pawn);
		Player1Pawn->DynamicMaterial->SetVectorParameterValue(FName("Color"), FColor::Blue);
	}
	if (!bIsCoop) return;
	
	if (APlayer2AIController* Player2AIController = GetWorld()->SpawnActor<APlayer2AIController>(APlayer2AIController::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player 2 controller created"));
		AMyPawn* Player2Pawn = GetWorld()->SpawnActor<AMyPawn>(PlayerClass, FVector(-250.0f, -60.0f, 21.0f), Rotation, SpawnInfo);
		Player2Pawn->Position = 1;
		Player2AIController->Possess(Player2Pawn);
		Player2Pawn->DynamicMaterial->SetVectorParameterValue(FName("Color"), FColor::Black);
	}
}

int32 AEndlessRunnerGameModeBase::GetLanes() const
{
	return Lanes;
}

void AEndlessRunnerGameModeBase::ReportDeadPlayer()
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

void AEndlessRunnerGameModeBase::SpawnInitialPlatforms()
{
	UWorld* World = GetWorld();
	const FRotator Rotation(0.0f, 0.0f, 0.0f);
	TArray<AMyPlatform*> TempPlatforms;
	for (int i = 0; i < Amount; i++)
	{
		const FActorSpawnParameters SpawnInfo;
		FVector Location(-200 * i, 0.0f, 0.0f);
		AMyPlatform* Platform = World->SpawnActor<AMyPlatform>(PlatformClass, Location, Rotation, SpawnInfo);
		PlatformPool.Enqueue(Platform);
		TempPlatforms.Add(Platform);
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
	

	for (int i = 0; i < TempPlatforms.Num(); i++)
	{
		TempPlatforms[i]->NextPlatform = TempPlatforms[(i + 1) % TempPlatforms.Num()];
	}
	
	PlatformPool.Peek(TailPlatform);
}

