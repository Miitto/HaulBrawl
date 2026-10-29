// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChaosWheeledVehicleMovementComponent.h"
#include "CoreMinimal.h"
#include "HBWheeledVehicleMvmntComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Physics), meta = (BlueprintSpawnableComponent))
class HAULBRAWL_API UHBWheeledVehicleMvmntComponent : public UChaosWheeledVehicleMovementComponent {
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Vehicle Setup")
  float GetMass() const;

  UFUNCTION(BlueprintCallable, Category = "Vehicle Setup")
  void SetMassAndRegenerate(float NewMass);
};
