// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("GameLevel"), false);
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HighscoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Highscore")));
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));

	FString Highscore;
	const FString FilePath = FPaths::ProjectDir() + TEXT("Highscore.txt");
	FFileHelper::LoadFileToString(Highscore, *FilePath);
	HighscoreText->SetText(FText::FromString(Highscore));

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMenuWidget::StartGame);
	}
}
