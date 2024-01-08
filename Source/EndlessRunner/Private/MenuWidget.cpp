// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MyGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("GameLevel"), false);
}

void UMenuWidget::SoloGame()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GameInstance->SetIsCoop(false);
	StartGame();
}

void UMenuWidget::CoopGame()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	GameInstance->SetIsCoop(true);
	StartGame();
}

void UMenuWidget::UpdateLanes(const float Value)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (!GameInstance) return;
	if (LanesSlider->GetValue() == 0)
	{
		GameInstance->SetLanes(3);
		LanesText->SetText(FText::FromString(TEXT("Lanes: 3")));
		return;
	}
	if (LanesSlider->GetValue() == 1)
	{
		GameInstance->SetLanes(5);
		LanesText->SetText(FText::FromString(TEXT("Lanes: 5")));
		return;
	}
	GameInstance->SetLanes(7);
	LanesText->SetText(FText::FromString(TEXT("Lanes: 7")));
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HighscoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Highscore")));
	LanesSlider = Cast<USlider>(GetWidgetFromName(TEXT("LanesSlider")));
	LanesText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SliderText")));

	FString Highscore;
	const FString FilePath = FPaths::ProjectDir() + TEXT("Highscore.txt");
	FFileHelper::LoadFileToString(Highscore, *FilePath);
	HighscoreText->SetText(FText::FromString(Highscore));

	if (StartSoloButton)
	{
		StartSoloButton->OnClicked.AddDynamic(this, &UMenuWidget::SoloGame);
	}

	if (StartCoopButton)
	{
		StartCoopButton->OnClicked.AddDynamic(this, &UMenuWidget::CoopGame);
	}

	if (LanesSlider && LanesText)
	{
		LanesSlider->OnValueChanged.AddDynamic(this, &UMenuWidget::UpdateLanes);
	}

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		LanesSlider->SetValue((GameInstance->GetLanes()-3)/2);
		LanesText->SetText(FText::FromString(FString::Printf(TEXT("Lanes: %d"), GameInstance->GetLanes())));
	}
}
