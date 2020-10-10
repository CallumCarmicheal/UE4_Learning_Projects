// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/STrackerBot.h"
#include "Components/SHealthComponent.h"
#include "SCharacter.h"

#include <GameFramework/Character.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet\GameplayStatics.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>
#include <DrawDebugHelpers.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/SphereComponent.h>

// Sets default values
ASTrackerBot::ASTrackerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(200);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ASTrackerBot::HandleTakeDamage);
	
	bUseVelocityChange = false;
	MovementForce = 1000;
	RequiredDistanceToTarget = 100;

	ExplosionDamage = 40;
	ExplosionRadius = 200;

	bFlashInSectionsOnSelfDestruct = false;
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();

	NextNavigationPoint = GetNextPathPoint();
}

UNavigationPath* ASTrackerBot::GetNavigationPath() {
	// Get the target player
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Get the navigation path
	UNavigationPath* Path = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);

	// Return the path
	return Path;
}

FVector ASTrackerBot::GetNextPathPoint() {
	// Get the target player
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Get the navigation path
	UNavigationPath* Path = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);
	
	// Return the next component in the path
	if (Path && Path->PathPoints.Num() > 1)
		return Path->PathPoints[1];
	
	UE_LOG(LogTemp, Log, TEXT("%d points for %s, P Vec: %s"), 
		(!Path ? -1 : Path->PathPoints.Num()), 
		*GetName(), 
		*PlayerPawn->GetActorLocation().ToString()
	);

	// There are not multiple points, return a direct vector to the target location
	return GetActorLocation();
}

// Called every frame
void ASTrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float DistanceToTarget = (GetActorLocation() - NextNavigationPoint).Size();
	
	if (DistanceToTarget <= RequiredDistanceToTarget) {
		NextNavigationPoint = GetNextPathPoint();

		DrawDebugString(GetWorld(), GetActorLocation(), "Target Reached", 0, FColor::White, 5);
	}

	else {
		// TODO: Detect if the bot is stuck and then recalculate a path to the player.
		// Calculate next waypoint, try to go to it. If it fails attempt to run a full nav simulation.
		
		// Keep moving towards next target
		FVector ForceDirection = NextNavigationPoint - GetActorLocation();
		ForceDirection.Normalize();

		ForceDirection *= MovementForce;
		MeshComp->AddForce(ForceDirection, NAME_None, bUseVelocityChange);

		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + ForceDirection, 32, 
			FColor::Magenta, false, 0.0f, 0, 3.0f);
	}

	DrawDebugSphere(GetWorld(), NextNavigationPoint, 20, 12, FColor::Purple, false, 0.0f, 1.0f);
}

void ASTrackerBot::HandleTakeDamage(USHealthComponent* HealthComponent, float Health, float HealthDelta,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) {

	// Create a dynamic material instance
	if (MatInst == nullptr) {
		MatInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));
		UE_LOG(LogTemp, Log, TEXT("Tracker %s: Created a new material instance"), *GetName());
	}
		
	// If the material is set/created then we want to set the world time
	if (MatInst) {
		MatInst->SetScalarParameterValue("LastTimeDamageTaken", GetWorld()->TimeSeconds);
		UE_LOG(LogTemp, Log, TEXT("Tracker %s: Set the value of LastTimeDamageTaken"), *GetName());
	}
	
	// Explode on HP == 0
	if (Health <= 0.00f) 
		SelfDestruct();

	UE_LOG(LogTemp, Log, TEXT("Health %s of %s"), *FString::SanitizeFloat(Health), *GetName());
}

void ASTrackerBot::SelfDestruct() {
	if (bExploded) return;
	bExploded = true;

	// If we have an effect spawn it.
	if (ExplosionEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	// Ignore ourself from the damage
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	// Apply damage
	UGameplayStatics::ApplyRadialDamage(this,
		ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr,
		IgnoredActors, this, GetInstigatorController(), true);

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 12, FColor::Red, false, 2.0f, 0, 1.0f);
	
	// Delete actor immediately.
	Destroy();
}

void ASTrackerBot::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (bStartedSelfDestruction) return;
	
	ASCharacter* PlayerPawn = Cast<ASCharacter>(OtherActor);

	if (PlayerPawn) {
		// We have overlapped the player
		bStartedSelfDestruction = true;

		// Set material to flash entirely if set in config
		if (!MatInst) 
			MatInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));
		
		MatInst->SetScalarParameterValue("FlashInSectionsOnDamage", bFlashInSectionsOnSelfDestruct);
		
		// Start self destruction sequence.
		GetWorldTimerManager().SetTimer(TimerHandle_SelfDamage, this, &ASTrackerBot::DamageSelf, 0.5f, true, 0.0f);
	}
}

void ASTrackerBot::DamageSelf() {
	UGameplayStatics::ApplyDamage(this, 20, GetInstigatorController(), this, nullptr);
}