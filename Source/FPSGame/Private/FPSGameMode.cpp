// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameVersion.generated.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	// Set our build information (for use in blueprints)
	VersionMajor = BUILD_MAJOR_VERSION;
	VersionMinor = BUILD_MINOR_VERSION;
	VersionPatch = BUILD_PATCH_VERSION;
	BuildNumber = BUILD_BUILD_NUMBER;
	BuildDate = FString(TEXT(BUILD_BUILD_DATE));
	BuildTime = FString(TEXT(BUILD_BUILD_TIME));
	GitHash = FString(TEXT(BUILD_GIT_HASH));

}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess) {
	UE_LOG(LogTemp, Log, TEXT("GameMode, CompleteMission called"));

	// If we have a valid pawn
	if (InstigatorPawn) {
		UE_LOG(LogTemp, Log, TEXT("Disabling InstigatorPawn's input."));

		InstigatorPawn->DisableInput(nullptr);

		// Check if the spectating class was set.
		if (SpectatingViewpointClass) {
			// Find all AActors of spectating class
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			// Change viewtargets if any valid actor is found
			if (ReturnedActors.Num() > 0) {
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				if (PC)
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}

		else {
			// The spectator class is not found
			UE_LOG(LogTemp, Log, TEXT("FPSGameMode: SpectatingViewpointClass is nullptr. Please update GameMode Class class with a valid subclass. Cannot change spectating viewtarget."));
		}
	}

	// Invoke the blueprint event.
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}