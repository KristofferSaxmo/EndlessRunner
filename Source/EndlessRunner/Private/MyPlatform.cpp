// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatform.h"
#include "Components/SceneComponent.h"
#include "EndlessRunner/EndlessRunnerGameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyPlatform::AMyPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootScene);
}

void AMyPlatform::BeginPlay()
{
	Super::BeginPlay();
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(this));
	const int32 LaneCount = GameMode->GetLanes();
	for (int32 i = -(LaneCount-1)/2; i <= (LaneCount-1)/2; i++)
	{
		Lanes.Add(FVector(0.0f, i*60.0f, 0.0f));
	}
	int32 RoundedUp = FMath::DivideAndRoundUp(Lanes.Num(), 2);
	Mesh->SetRelativeScale3D(FVector(2.0f, static_cast<float>(RoundedUp), 2.0f));

}

void AMyPlatform::SpawnObstacles()
{
	TArray<int32> LaneIndices;
	for (int32 i = 0; i < Lanes.Num(); i++)
	{
		LaneIndices.Add(i);
	}
	const int32 LanesRounded = FMath::DivideAndRoundUp(Lanes.Num(), 2);
	const int32 EmptyLanesCount = FMath::RandRange(LanesRounded - 1, LanesRounded);
	
	for (int32 i = 0; i < LaneIndices.Num(); ++i)
	{
		const int32 j = FMath::RandRange(0, LaneIndices.Num() - 1);
		Swap(LaneIndices[i], LaneIndices[j]);
	}

	for (int32 i = 0; i < LaneIndices.Num(); ++i)
	{
		if (i < EmptyLanesCount)
		{
			FreeLanes.Add(-(LaneIndices[i] - (LanesRounded - 1)));
			continue;
		}

		const FActorSpawnParameters SpawnInfo;
		const FRotator Rotation(0.0f, 0.0f, 0.0f);
		AActor* Barrel = GetWorld()->SpawnActor<AActor>(BarrelClass, Lanes[LaneIndices[i]], Rotation, SpawnInfo);
		Barrel->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

int32 AMyPlatform::DeleteObstacles()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	int32 Count = 0;
	for (AActor* AttachedActor : AttachedActors)
	{
		Count++;
		AttachedActor->Destroy();
	}
	FreeLanes.Empty();
	return Count;
}

void AMyPlatform::DeleteObstacle()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	if (AttachedActors.Num() > 0)
	{
		const float YPos = AttachedActors[0]->GetActorLocation().Y;
		FreeLanes.Add(-(YPos / 60.0f));
		AttachedActors[0]->Destroy();
	}
}

void AMyPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * Velocity * DeltaTime;
	SetActorLocation(Location);
}

