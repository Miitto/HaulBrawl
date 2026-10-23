// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HaulBrawlVehiclePawn.h"

#include "HaulBrawlSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class AHaulBrawlSportsCar : public AHaulBrawlVehiclePawn {
  GENERATED_BODY()

public:
  AHaulBrawlSportsCar();
};
