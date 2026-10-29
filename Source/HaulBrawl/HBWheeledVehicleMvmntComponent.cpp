// Fill out your copyright notice in the Description page of Project Settings.

#include "HBWheeledVehicleMvmntComponent.h"

float UHBWheeledVehicleMvmntComponent::GetMass() const { return Mass; }

void UHBWheeledVehicleMvmntComponent::SetMassAndRegenerate(float NewMass) {
  Mass = NewMass;
  RecreatePhysicsState();
}