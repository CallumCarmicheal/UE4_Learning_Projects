// Fill out your copyright notice in the Description page of Project Settings.


#include "CCGameGlobals.h"

#include "CoopGame.h"
#include "GameVersion.generated.h"

#include "Kismet/GameplayStatics.h"


#define STR_IMPL_(x) #x      //stringify argument
#define STR(x) STR_IMPL_(x)  //indirection to expand argument macros

FName UCCGameGlobals::GetGameBuildVersion() {
	// Return a const string
	return
		"COOPGame DEVELOPMENT "
		"BUILD(" STR(BUILD_BUILD_NUMBER) ") "
		BUILD_BUILD_DATE " " BUILD_BUILD_TIME
		" # " BUILD_GIT_HASH;
}

static int32 UIVersionInformation = 0;
FAutoConsoleVariableRef CVAR_UIVersionInformation(
	TEXT(CC_CONSOLE_PREFIX "UI.VersionInformation"),
	UIVersionInformation,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_SetByGameSetting);