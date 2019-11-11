// Fill out your copyright notice in the Description page of Project Settings.

#include "AFPSEngineUtility.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void AFPSEngineUtility::AddOnScreenDebugMessage(uint64 Key, float TimeToDisplay, FColor DisplayColor,
		const FString& DebugMessage, bool bNewerOnTop, const FVector2D& TextScale) {
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage, bNewerOnTop, TextScale);
}

void AFPSEngineUtility::AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor,
		const FString& DebugMessage, bool bNewerOnTop, const FVector2D& TextScale) {
	GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, DisplayColor, DebugMessage, bNewerOnTop, TextScale);
}