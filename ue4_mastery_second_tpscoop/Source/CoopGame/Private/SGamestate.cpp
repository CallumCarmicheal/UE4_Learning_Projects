// Fill out your copyright notice in the Description page of Project Settings.


#include "SGamestate.h"
#include "GameVersion.generated.h"

ASGamestate::ASGamestate() {
	// Set our build information (for use in blueprints)
	VersionMajor = BUILD_MAJOR_VERSION;
	VersionMinor = BUILD_MINOR_VERSION;
	VersionPatch = BUILD_PATCH_VERSION;
	BuildNumber  = BUILD_BUILD_NUMBER;
	BuildDate	 = FString(TEXT(BUILD_BUILD_DATE));
	BuildTime	 = FString(TEXT(BUILD_BUILD_TIME));
	GitHash		 = FString(TEXT(BUILD_GIT_HASH));
}