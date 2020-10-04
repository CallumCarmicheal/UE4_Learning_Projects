// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/STrackerBot.h"

#include <GameFramework/Character.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet\GameplayStatics.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>

// Sets default values
ASTrackerBot::ASTrackerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);

	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();
	
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
	UNavigationPath* Path = GetNavigationPath();

	// Return the next component in the path
	if (Path->PathPoints.Num() > 1)
		return Path->PathPoints[0];

	// There are not multiple points, return a direct vector to the target location
	return GetActorLocation();
}

// Called every frame
void ASTrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

