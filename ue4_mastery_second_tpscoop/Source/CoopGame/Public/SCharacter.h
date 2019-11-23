// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ASWeapon;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
protected: // Input Methods
	void InputMoveForward(float Value);
	void InputMoveRight(float Value);

	void InputBeginCrouch();
	void InputEndCrouch();
	
	void InputBeginZoom();
	void InputEndZoom();

	void InputStartFire();
	void InputEndFire();
	
protected: // Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

protected: // Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;
	
	/**
	 * If the camera wants to zoom.
	 */
	bool bWantsToZoom;

	/**
	 * FOV to be set while Zooming in.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (DisplayName = "FOV Zoomed"))
	float FOVZoomed;

	/**
	 * The Interp speed for Zooming
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100.0))
	float ZoomInterpSpeed;
	
	/**
	 * Default FOV set during BeginPlay.
	 *
	 * Hidden from designer as its set at runtime not in constructor.
	 * If you want to see this in the designer use:
	 *		UPROPERTY(VisibleDefaultsOnly, Category = "Player") 
	 */
	float FOVDefault;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;
};
