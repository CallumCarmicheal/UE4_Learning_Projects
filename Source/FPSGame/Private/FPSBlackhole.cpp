// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackhole.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"

// Sets default values
AFPSBlackhole::AFPSBlackhole() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Physical Viewport Mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	// Deletion Sphere
	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponent->SetSphereRadius(100);
	InnerSphereComponent->SetupAttachment(MeshComp);
	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackhole::OverlapInnerSphere);

	// Attraction Spehere
	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComponent->SetSphereRadius(3000);
	OuterSphereComponent->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSBlackhole::BeginPlay() {
	Super::BeginPlay();
}

void AFPSBlackhole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor)
		OtherActor->Destroy();
}

// Called every frame
void AFPSBlackhole::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Find all overlapping components that can collide and may be physically simulating
	TArray<UPrimitiveComponent*> taOverlappingComponents;
	OuterSphereComponent->GetOverlappingComponents(taOverlappingComponents);

	for (int i = 0; i < taOverlappingComponents.Num(); i++) {
		UPrimitiveComponent* actor = taOverlappingComponents[i];

		if (actor && actor->IsSimulatingPhysics()) {
			// The component we are looking for! It needs to be simulating in order to apply forces.

			const float SphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000; // Negative value to make it pull towards the origin instead of pushing

			actor->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}