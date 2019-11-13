// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Enable crouching.
	auto navProperties = GetMovementComponent()->GetNavAgentPropertiesRef();
	navProperties.bCanCrouch = true;
	navProperties.bCanJump = true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay() {
	Super::BeginPlay();
	
}

void ASCharacter::InputMoveForward(float Value) {
	AddMovementInput(GetActorForwardVector() * Value);
}

void ASCharacter::InputMoveRight(float Value) {
	AddMovementInput(GetActorRightVector() * Value);
}

void ASCharacter::InputBeginCrouch() {
	Crouch();
}

void ASCharacter::InputEndCrouch() {
	UnCrouch();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::InputMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",	  this, &ASCharacter::InputMoveRight);

	PlayerInputComponent->BindAxis("LookUp",		this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight",	this, &ASCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch",	IE_Pressed,  this, &ASCharacter::InputBeginCrouch);
	PlayerInputComponent->BindAction("Crouch",	IE_Released, this, &ASCharacter::InputEndCrouch);

	PlayerInputComponent->BindAction("Jump",		IE_Pressed, this, &ACharacter::Jump);
}

FVector ASCharacter::GetPawnViewLocation() const {
	if (CameraComp)
		return CameraComp->GetComponentLocation();
	
	return Super::GetPawnViewLocation();
}
