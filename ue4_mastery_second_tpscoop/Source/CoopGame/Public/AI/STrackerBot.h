 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STrackerBot.generated.h"

class USHealthComponent;
class UNavigationPath;
class UMaterialInstanceDynamic;
class UParticleSystem;

UCLASS()
class COOPGAME_API ASTrackerBot : public APawn
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this pawn's properties
	ASTrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeDamage(USHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SelfDestruct();
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USHealthComponent* HealthComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION(BlueprintCallable)
	FVector GetNextPathPoint();

	UFUNCTION(BlueprintCallable)
	UNavigationPath* GetNavigationPath();

	UPROPERTY(BlueprintReadOnly, Category = "Tracker Bot")
	FVector NextNavigationPoint;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	float MovementForce;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	bool bUseVelocityChange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	float RequiredDistanceToTarget;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(BlueprintReadOnly, Category = "Tracker Bot")
	bool bExploded;
	
	/// <summary>
	/// Dynamic Material to pulse on damage
	/// </summary>
	UMaterialInstanceDynamic* MatInst;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	float ExplosionRadius;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Tracker Bot")
	float ExplosionDamage;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
