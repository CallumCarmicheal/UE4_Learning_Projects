// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

#include "GameVersion.generated.h"
#include "Engine/World.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Set our custom gamemode classes
	HUDClass = AFPSHUD::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
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

			// Change view targets if any valid actor is found
			if (ReturnedActors.Num() > 0) {
				AActor* NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
					APlayerController* PC = it->Get();

					if (PC) 
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}

		else {
			// The spectator class is not found
			UE_LOG(LogTemp, Log, TEXT("FPSGameMode: SpectatingViewpointClass is nullptr. Please update GameMode Class class with a valid subclass. Cannot change spectating viewtarget."));
		}
	}

	// Invoke the Multicast Mission Complete event
	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS) {
		GS->MulticastOnMissionCompleted(InstigatorPawn, bMissionSuccess);
	}
	
	// Invoke the blueprint event.
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}