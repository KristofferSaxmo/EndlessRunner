// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "EnhancedInputComponent.h"
#include "EndlessRunner/EndlessRunnerGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Player1Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetSimulatePhysics(true);
	Body->SetCollisionProfileName("Pawn");
	RootComponent = Body;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		Body->SetStaticMesh(CubeMesh.Object);
	}

	Body->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* Material = Body->GetMaterial(0); // Get the material at index 0
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	Body->SetMaterial(0, DynamicMaterial);
}

void AMyPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor->ActorHasTag("Obstacle")) return;
	OtherActor->Destroy();
	Health -= 1;
	AEndlessRunnerGameModeBase* GameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(this));
	APlayer1Controller* PlayerController = Cast<APlayer1Controller>(GetController());
	if (PlayerController)
	{
		GameMode->PlayerHUD->UpdateHealth(Health);
	}
	GameMode->PlayerHUD->UpdateHealth(Health);
	if (Health == 0)
	{
		if (PlayerController)
		{
			GameMode->ReportDeadPlayer();
		}
		Destroy();
	}
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPawn::Jump);
		EnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &AMyPawn::Move, true);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyPawn::Move, false);
	}
}

void AMyPawn::Jump()
{
	if (GetActorLocation().Z > 20.1f) return;

	Body->SetPhysicsLinearVelocity(FVector::Zero());
	Body->AddImpulse(FVector(0, 0, JumpVelocity), NAME_None, true);
}

void AMyPawn::Move(bool bLeft)
{
	const int32 Lanes = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(this))->GetLanes();
	if (!bLeft && Position == (Lanes-1)/2) return;
	if (bLeft && Position == -(Lanes-1)/2) return;
	bLeft ? Position-- : Position++;

	FVector Location = GetActorLocation();
	Location.Y = -Position * MoveLength;
	SetActorLocation(Location);
}