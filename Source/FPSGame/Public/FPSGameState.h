// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		int VersionMajor;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		int VersionMinor;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		int VersionPatch;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		int BuildNumber;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		FString BuildDate;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		FString BuildTime;
	UPROPERTY(BlueprintReadOnly, Category = "Build")
		FString GitHash;
	
public:
	AFPSGameState();

	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
};
