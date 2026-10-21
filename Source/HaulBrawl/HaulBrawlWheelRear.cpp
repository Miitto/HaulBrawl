// Copyright Epic Games, Inc. All Rights Reserved.

#include "HaulBrawlWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UHaulBrawlWheelRear::UHaulBrawlWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}