// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMyPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyPlatform();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Velocity;

protected:
	TArray<AActor> Obstacles;
	TArray<FVector> Lanes;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Obstacles")
	TSubclassOf<AActor> BarrelClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	class USceneComponent* RootScene;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveActor")
	class UStaticMeshComponent* Mesh;

public:
	void SpawnObstacles();
	void DeleteObstacles() const;
	virtual void Tick(float DeltaTime) override;
};
