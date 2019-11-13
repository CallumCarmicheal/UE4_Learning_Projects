// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire() {
	const float HIT_TRACE_LENGTH = 10000.0f;
	const float WeaponDamage = 20.0f;
	
	// Trace the world from the pawn eye's to the cross-hair location

	AActor* pOwner = GetOwner();
	if (pOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		pOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * HIT_TRACE_LENGTH);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(pOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		
		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams)) {
			// Hit object, Process Damage.
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, WeaponDamage, ShotDirection, Hit, pOwner->GetInstigatorController(), this, DamageType);
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
	}
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

