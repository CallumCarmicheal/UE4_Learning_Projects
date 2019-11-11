// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone() {
	// Create the collision zone
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	OverlapComp->SetHiddenInGame(false); // Show the bounds while debugging ingame
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
	RootComponent = OverlapComp;

	// Extraction Zone decal
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {

	// Attempt to cast our pawn, if not return.
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (!MyPawn) return;

	UE_LOG(LogTemp, Log, TEXT("Extraction Zone, MyPawn = %d, IsCarrying = %d!"), MyPawn != nullptr, MyPawn ? MyPawn->bIsCarryingObjective : 0);

	// If we are carrying the objective
	if (MyPawn->bIsCarryingObjective) {
		// Invoke complete mission
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GM)
			GM->CompleteMission(MyPawn, true);
		//else { UE_LOG(LogTemp, Log, TEXT("FPSExtractionZone: Failed to cast gamemode!")); }
	}

	else {
		// Play the sound
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}