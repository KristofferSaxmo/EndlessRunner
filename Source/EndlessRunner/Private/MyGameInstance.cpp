// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
    Lanes = 5;
    bIsCoop = false;
}

int32 UMyGameInstance::GetLanes() const
{
    return Lanes;
}

void UMyGameInstance::SetLanes(const int32 Value)
{
    Lanes = Value;
}

bool UMyGameInstance::GetIsCoop() const
{
    return bIsCoop;
}

void UMyGameInstance::SetIsCoop(const bool Value)
{
    bIsCoop = Value;
}
