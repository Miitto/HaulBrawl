// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HaulBrawlPlayerController.generated.h"

class UInputMappingContext;
class AHaulBrawlVehiclePawn;
class UHaulBrawlUI;
class AHaulBrawlOnFootCharacter;

/**
 *  Vehicle Player Controller class
 *  Handles input mapping and user interface
 */
UCLASS(abstract, Config = "Game")
class AHaulBrawlPlayerController : public APlayerController {
  GENERATED_BODY()

protected:
  /** Input Mapping Contexts */
  UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
  TArray<UInputMappingContext*> DefaultVehicleMappingContexts;

  /** If true, the optional steering wheel input mapping context will be registered */
  UPROPERTY(EditAnywhere, Category = "Input|Steering Wheel Controls")
  bool bUseSteeringWheelControls = false;

  /** Optional Input Mapping Context to be used for steering wheel input.
   *  This is added alongside the default Input Mapping Context and does not block other forms of input.
   */
  UPROPERTY(EditAnywhere, Category = "Input|Steering Wheel Controls", meta = (EditCondition = "bUseSteeringWheelControls"))
  UInputMappingContext* SteeringWheelInputMappingContext;

  UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
  TArray<UInputMappingContext*> DefaultOnFootMappingContexts;

  /** Type of vehicle to automatically respawn when it's destroyed */
  UPROPERTY(EditAnywhere, Category = "Vehicle|Respawn")
  TSubclassOf<AHaulBrawlVehiclePawn> VehiclePawnClass;

  /** Pointer to the controlled pawn */
  TObjectPtr<APawn> ActivePawn;

  /** Type of the UI to spawn */
  UPROPERTY(EditAnywhere, Category = "Vehicle|UI")
  TSubclassOf<UHaulBrawlUI> VehicleUIClass;

  /** Pointer to the UI widget */
  UPROPERTY()
  TObjectPtr<UHaulBrawlUI> VehicleUI;

  UPROPERTY(EditAnywhere, Category = "On Foot")
  TSubclassOf<AHaulBrawlOnFootCharacter> OnFootPawnClass;

  bool bIsInVehicle = true;

protected:
  /** Gameplay initialization */
  virtual void BeginPlay() override;

  /** Input setup */
  virtual void SetupInputComponent() override;

  /** Pawn setup */
  virtual void OnPossess(APawn* InPawn) override;
  virtual void OnUnPossess() override;

  /** Handles pawn destruction and respawning */
  UFUNCTION()
  void OnPawnDestroyed(AActor* DestroyedPawn);

public:
  void GetOutVehicle();
  void GetInVehicle(AHaulBrawlVehiclePawn* veh);

  /** Update vehicle UI on tick */
  virtual void Tick(float Delta) override;
};
