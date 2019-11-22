// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVAR_DebugWeaponDrawing (
	TEXT("COOP.Debug.WeaponDrawing"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_Cheat);

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "Socket_Weapon_Muzzle";
	TracerTargetName = "Target";
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

		// Particle "Target" Parameter
		FVector TracerEndPoint = TraceEnd;
		
		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams)) {
			// Hit object, Process Damage.
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, WeaponDamage, ShotDirection, Hit, pOwner->GetInstigatorController(), this, DamageType);

			if (ImpactEffect)
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

			TracerEndPoint = Hit.ImpactPoint;
		}

		if (DebugWeaponDrawing > 0)
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);

		// 
		PlayFireEffects(TracerEndPoint);
	}
}

void ASWeapon::PlayFireEffects(const FVector TracerEndPoint) const {
	if (MuzzleEffect)
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);

	if (TracerEffect) {
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		UParticleSystemComponent* pTracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
		if (pTracerComponent)
			pTracerComponent->SetVectorParameter(TracerTargetName, TracerEndPoint);
	}
}