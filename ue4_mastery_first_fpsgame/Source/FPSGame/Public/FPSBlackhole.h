// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackhole.generated.h"

class USphereComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;

UCLASS()
class FPSGAME_API AFPSBlackhole : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSBlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* InnerSphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* OuterSphereComponent;

	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Blackhole")
		bool IsEnabled;

};
