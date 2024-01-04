// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyPlatform.h"
#include "PlayerHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Queue.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AMyPawn;
class AMyPlatform;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEndlessRunnerGameModeBase();
	
	void ReportDeadPlayer();

	UPROPERTY()
	UPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPlayerHUD> PlayerHudClass;
	
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
	
	
protected:
	TQueue<AMyPlatform*> PlatformPool;
	TArray<AMyPlatform*> Platforms;
	void SpawnInitialPlatforms();

	AMyPlatform* TailPlatform;
	AMyPlatform* HeadPlatform;
	
	
	int32 Counter;
	float Timer;
	int32 Score;
	int32 PlayersAlive;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platforms")
	int32 PlatformsPerObstacle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platforms")
	TSubclassOf<AMyPlatform> PlatformClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platforms")
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platforms")
	float Acceleration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Platforms")
	int32 Amount;
};
