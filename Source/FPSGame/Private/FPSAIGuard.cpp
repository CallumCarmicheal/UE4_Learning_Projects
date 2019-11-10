// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "FPSGameMode.h"
#include "AFPSEngineUtility.h"

#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sensing Component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

void AFPSAIGuard::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Sensing Component
	//   Add the OnSeePawn event
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	//   Add the Hear Event
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}


// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay() {
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
}

/**
 * Called when a pawn has been seen by the actor
 * @param SeenPawn
 */
void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn) {
	if (SeenPawn == nullptr) return;

	AFPSEngineUtility::AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("FPSAIGuard: %s Noticed character %s!"), *GetName(), *SeenPawn->GetName()));

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	// Invoke mission failed
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	GM->CompleteMission(SeenPawn, false);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInvestigator, const FVector& Location, float Volume) {
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.00f;
	NewLookAt.Roll = 0.00f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
}