// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlatform.h"
#include "Components/SceneComponent.h"


// Sets default values
AMyPlatform::AMyPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyPlatform::BeginPlay()
{
	Super::BeginPlay();
	Lanes.Add(FVector(0.0f, -60.0f, 0.0f));
	Lanes.Add(FVector(0.0f, 0.0f, 0.0f));
	Lanes.Add(FVector(0.0f, 60.0f, 0.0f));
}

void AMyPlatform::SpawnObstacles()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	TArray<int32> LaneIndices = {0, 1, 2};
	const int32 EmptyLanesCount = FMath::RandBool() ? 1 : 2;
	for (int32 i = 0; i < LaneIndices.Num(); ++i)
	{
		const int32 j = FMath::RandRange(0, LaneIndices.Num() - 1);
		Swap(LaneIndices[i], LaneIndices[j]);
	}

	for (int32 i = 0; i < LaneIndices.Num(); ++i)
	{
		if (i < EmptyLanesCount) continue;

		const FActorSpawnParameters SpawnInfo;
		const FRotator Rotation(0.0f, 0.0f, 0.0f);
		AActor* Barrel = World->SpawnActor<AActor>(BarrelClass, Lanes[LaneIndices[i]], Rotation, SpawnInfo);
		Barrel->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AMyPlatform::DeleteObstacles() const
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	
	for (AActor* AttachedActor : AttachedActors)
	{
		AttachedActor->Destroy();
	}
}

void AMyPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * Velocity * DeltaTime;
	SetActorLocation(Location);
}

