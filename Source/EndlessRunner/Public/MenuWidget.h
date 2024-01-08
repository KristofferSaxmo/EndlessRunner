// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void StartGame();

	UFUNCTION()
	void SoloGame();

	UFUNCTION()
	void CoopGame();

	UFUNCTION()
	void UpdateLanes(const float Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget")
	UTextBlock* HighscoreText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget")
	UTextBlock* LanesText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget", meta = (BindWidget))
	UButton* StartSoloButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget", meta = (BindWidget))
	UButton* StartCoopButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget", meta = (BindWidget))
	USlider* LanesSlider;

	virtual void NativeConstruct() override;
};
