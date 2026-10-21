// Copyright Epic Games, Inc. All Rights Reserved.

#include "HaulBrawlWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UHaulBrawlWheelFront::UHaulBrawlWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}