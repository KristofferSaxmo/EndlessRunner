// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION()
	void StartGame();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget")
	class UTextBlock* HighscoreText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuWidget", meta = (BindWidget))
	class UButton* StartButton;

	virtual void NativeConstruct() override;
};
