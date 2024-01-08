// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UMyGameInstance();
	int32 Lanes;
	bool bIsCoop;

public:
	int32 GetLanes() const;
	void SetLanes(const int32 Value);
	
	bool GetIsCoop() const;
	void SetIsCoop(const bool Value);
};
