// Fill out your copyright notice in the Description page of Project Settings.

#include "CCEngineUtility.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void CCEngineUtility::AddOnScreenDebugMessage(uint64 Key, float TimeToDisplay, FColor DisplayColor,
	const FString& DebugMessage, bool bNewerOnTop, const FVector2D& TextScale) {
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage, bNewerOnTop, TextScale);
}

void CCEngineUtility::AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor,
	const FString& DebugMessage, bool bNewerOnTop, const FVector2D& TextScale) {
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage, bNewerOnTop, TextScale);
}