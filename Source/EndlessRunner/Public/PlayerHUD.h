// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHUD")
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerHUD")
	class UTextBlock* HealthText;

	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void UpdateScore(int32 Score);
	
	UFUNCTION()
	void UpdateHealth(int32 Health);
};
