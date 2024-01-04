// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "EndlessRunner/EndlessRunnerGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor->ActorHasTag("Obstacle")) return;
	OtherActor->Destroy();
	Health -= 1;
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(this));
	GameMode->PlayerHUD->UpdateHealth(Health);
	if (Health == 0)
	{
		GameMode->ReportDeadPlayer();
		Destroy();
	}
}

