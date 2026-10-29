// Copyright Epic Games, Inc. All Rights Reserved.

#include "HaulBrawlPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerStart.h"
#include "HBWheeledVehicleMvmntComponent.h"
#include "HaulBrawl.h"
#include "HaulBrawlOnFootCharacter.h"
#include "HaulBrawlUI.h"
#include "HaulBrawlVehiclePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AHaulBrawlPlayerController::BeginPlay() {
  Super::BeginPlay();

  // ensure we're attached to the vehicle pawn so that World Partition streaming works correctly
  bAttachToPawn = true;
}

void AHaulBrawlPlayerController::SetupInputComponent() {
  Super::SetupInputComponent();

  // only add IMCs and UI for local player controllers
  if (IsLocalPlayerController()) {
    // Add Input Mapping Contexts
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
      for (UInputMappingContext* CurrentContext : DefaultVehicleMappingContexts) {
        Subsystem->AddMappingContext(CurrentContext, 0);
      }

      if (bUseSteeringWheelControls) {
        Subsystem->AddMappingContext(SteeringWheelInputMappingContext, 0);
      }
    }

    // spawn the UI widget and add it to the viewport
    VehicleUI = CreateWidget<UHaulBrawlUI>(this, VehicleUIClass);

    if (VehicleUI) {
      VehicleUI->AddToPlayerScreen(0);

    } else {

      UE_LOG(LogHaulBrawl, Error, TEXT("Could not spawn vehicle UI widget."));
    }
  }
}

void AHaulBrawlPlayerController::Tick(float Delta) {
  Super::Tick(Delta);

  if (bIsInVehicle && IsValid(ActivePawn) && IsValid(VehicleUI)) {
    AHaulBrawlVehiclePawn* p = Cast<AHaulBrawlVehiclePawn>(ActivePawn);
    VehicleUI->UpdateSpeed(p->GetChaosVehicleMovement()->GetForwardSpeed());
    VehicleUI->UpdateGear(p->GetChaosVehicleMovement()->GetCurrentGear());
  }
}

void AHaulBrawlPlayerController::OnPossess(APawn* InPawn) {
  if (InPawn == ActivePawn)
    return;

  Super::OnPossess(InPawn);

  // get a pointer to the controlled pawn
  ActivePawn = InPawn;

  if (!ActivePawn)
    return;

  // subscribe to the pawn's OnDestroyed delegate
  ActivePawn->OnDestroyed.AddDynamic(this, &AHaulBrawlPlayerController::OnPawnDestroyed);
}

void AHaulBrawlPlayerController::OnUnPossess() {
  if (ActivePawn) {
    // unsubscribe from the pawn's OnDestroyed delegate
    ActivePawn->OnDestroyed.RemoveDynamic(this, &AHaulBrawlPlayerController::OnPawnDestroyed);
  }
  ActivePawn = nullptr;
  Super::OnUnPossess();
}

void AHaulBrawlPlayerController::OnPawnDestroyed(AActor* DestroyedPawn) {
  // Respawn the vehicle pawn at the player start.
  UE_LOG(LogHaulBrawl, Display, TEXT("Vehicle pawn %s destroyed. Respawning..."), *DestroyedPawn->GetName());

  // find the player start
  TArray<AActor*> ActorList;
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActorList);

  if (ActorList.Num() > 0) {
    // spawn a vehicle at the player start
    const FTransform SpawnTransform = ActorList[0]->GetActorTransform();

    if (AHaulBrawlVehiclePawn* RespawnedVehicle = GetWorld()->SpawnActor<AHaulBrawlVehiclePawn>(VehiclePawnClass, SpawnTransform)) {
      // possess the vehicle
      Possess(RespawnedVehicle);
    }
  }
}

void AHaulBrawlPlayerController::GetOutVehicle() {
  if (!bIsInVehicle)
    return;

  auto vehPawn = Cast<AHaulBrawlVehiclePawn>(ActivePawn);
  auto spawnPos = vehPawn->GetOnFootSpawnLocation();

  auto spawnTransform = FTransform(vehPawn->GetActorRotation(), spawnPos, FVector::OneVector);

  auto onFoot = GetWorld()->SpawnActor<AHaulBrawlOnFootCharacter>(OnFootPawnClass, spawnTransform);

  if (!onFoot) {
    UE_LOG(LogHaulBrawl, Error, TEXT("Could not spawn on foot character."));
    return;
  }

  vehPawn->OnGetOut();

  UnPossess();
  Possess(onFoot);
  bIsInVehicle = false;

  if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
    for (UInputMappingContext* CurrentContext : DefaultVehicleMappingContexts) {
      Subsystem->RemoveMappingContext(CurrentContext);
    }

    for (UInputMappingContext* CurrentContext : DefaultOnFootMappingContexts) {
      Subsystem->AddMappingContext(CurrentContext, 0);
    }
  }
}

void AHaulBrawlPlayerController::GetInVehicle(AHaulBrawlVehiclePawn* veh) {
  AHaulBrawlOnFootCharacter* onFoot = nullptr;

  if (bIsInVehicle) {
    auto veh = Cast<AHaulBrawlVehiclePawn>(ActivePawn);
    veh->OnGetOut();
  } else {
    onFoot = Cast<AHaulBrawlOnFootCharacter>(ActivePawn);
  }

  veh->OnGetIn();

  UnPossess();
  Possess(veh);

  if (onFoot != nullptr) {
    onFoot->Destroy();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
      for (UInputMappingContext* CurrentContext : DefaultOnFootMappingContexts) {
        Subsystem->RemoveMappingContext(CurrentContext);
      }

      for (UInputMappingContext* CurrentContext : DefaultVehicleMappingContexts) {
        Subsystem->AddMappingContext(CurrentContext, 0);
      }
    }
  }

  bIsInVehicle = true;
}