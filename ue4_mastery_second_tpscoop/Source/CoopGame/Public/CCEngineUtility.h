// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class COOPGAME_API CCEngineUtility
{
public:
	/** Add a FString to the On-screen debug message system. bNewerOnTop only works with Key == INDEX_NONE */
	static void AddOnScreenDebugMessage(uint64 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop = true, const FVector2D& TextScale = FVector2D::UnitVector);

	/** Add a FString to the On-screen debug message system. bNewerOnTop only works with Key == INDEX_NONE */
	static void AddOnScreenDebugMessage(int32 Key, float TimeToDisplay, FColor DisplayColor, const FString& DebugMessage, bool bNewerOnTop = true, const FVector2D& TextScale = FVector2D::UnitVector);

};
