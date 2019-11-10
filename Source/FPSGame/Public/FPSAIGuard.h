// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8 {
	/**
	 * The AI is not doing anything
	 */
	Idle,

	/**
	 * The AI is suspicious of a location
	 */
	Suspicious,

	/**
	 * The AI has noticed / seen a pawn.
	 */
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInvestigator, const FVector& Location, float Volume);

	// Setup our component events
	void PostInitializeComponents() override;
	
	FTimerHandle TimerHandle_ResetOrientation;
	FRotator OriginalRotation;

	UFUNCTION()
	void ResetOrientation();


	EAIState GuardState;
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChanged(EAIState NewState);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
