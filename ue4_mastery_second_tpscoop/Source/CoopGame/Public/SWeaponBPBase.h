// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.h"
#include "SWeaponBPBase.generated.h"

UCLASS()
class COOPGAME_API ASWeaponBPBase : public ASWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeaponBPBase();

protected:
	virtual void Fire();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnFire();
};
