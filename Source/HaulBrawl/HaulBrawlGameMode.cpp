// Copyright Epic Games, Inc. All Rights Reserved.

#include "HaulBrawlGameMode.h"
#include "HaulBrawlPlayerController.h"

AHaulBrawlGameMode::AHaulBrawlGameMode()
{
	PlayerControllerClass = AHaulBrawlPlayerController::StaticClass();
}
