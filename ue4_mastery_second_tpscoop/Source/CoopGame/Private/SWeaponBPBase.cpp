// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeaponBPBase.h"

// Sets default values
ASWeaponBPBase::ASWeaponBPBase()
{
	// 
}

void ASWeaponBPBase::Fire() {
	// We want to pass along the Fire event to the blueprint!
	OnFire();
}

