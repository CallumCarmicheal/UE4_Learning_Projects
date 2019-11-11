// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameVersion.generated.h"


AFPSGameState::AFPSGameState() {
	// Set our build information (for use in blueprints)
	VersionMajor = BUILD_MAJOR_VERSION;
	VersionMinor = BUILD_MINOR_VERSION;
	VersionPatch = BUILD_PATCH_VERSION;
	BuildNumber  = BUILD_BUILD_NUMBER;
	BuildDate	 = FString(TEXT(BUILD_BUILD_DATE));
	BuildTime	 = FString(TEXT(BUILD_BUILD_TIME));
	GitHash		 = FString(TEXT(BUILD_GIT_HASH));
}

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess) {
	for (auto it = AActor::GetWorld()->GetPawnIterator(); it; it++) {
		APawn* Pawn = it->Get();

		if (Pawn && Pawn->IsLocallyControlled()) {
			Pawn->DisableInput(nullptr);
		}
	}
}
