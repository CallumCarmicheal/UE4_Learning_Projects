// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#include "GameVersion.generated.h"
#include "FPSPlayerController.h"


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

void AFPSGameState::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool bMissionSuccess) {
	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(it->Get());
		if (PC && PC->IsLocalController()) {
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// Disable input's
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
				MyPawn->DisableInput(PC);
		}
	}
}
