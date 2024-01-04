// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/TextBlock.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ScoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScoreCount")));
	HealthText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HealthCount")));
	ScoreText->SetText(FText::FromString(FString::FromInt(0)));
	HealthText->SetText(FText::FromString(FString::FromInt(3)));
}

void UPlayerHUD::UpdateHealth(int32 Health)
{
	HealthText->SetText(FText::FromString(FString::FromInt(Health)));
}

void UPlayerHUD::UpdateScore(int32 Score)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}