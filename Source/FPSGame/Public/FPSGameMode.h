// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase {
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectator")
		TSubclassOf<AActor> SpectatingViewpointClass;

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
	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

};



