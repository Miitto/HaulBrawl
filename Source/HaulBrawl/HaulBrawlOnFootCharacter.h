// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HaulBrawlOnFootCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UCharacterMovementComponent;
class AHaulBrawlVehiclePawn;

UCLASS(abstract)
class HAULBRAWL_API AHaulBrawlOnFootCharacter : public ACharacter {
  GENERATED_BODY()

protected:
  UPROPERTY(EditAnywhere, Category = "Input")
  UInputAction* MoveAction;

  UPROPERTY(EditAnywhere, Category = "Input")
  UInputAction* LookAction;

  UPROPERTY(EditAnywhere, Category = "Input")
  UInputAction* GetInAction;

  TObjectPtr<UCharacterMovementComponent> CharacterMovement;

  UPROPERTY(EditAnywhere, Category = "Vehicle")
  UMaterialInterface* VehicleOutlineMaterial;

  UPROPERTY(EditAnywhere, Category = "Vehicle")
  float VehicleScanDistance = 100.f;

  UPROPERTY(EditAnywhere, Category = "Vehicle")
  float VehicleScanInterval = 0.2f;

  float TimeTillVehicleScan = 0.f;

  AHaulBrawlVehiclePawn* CurrentlyHighlightedVehicle = nullptr;

public:
  // Sets default values for this pawn's properties
  AHaulBrawlOnFootCharacter();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  void Move(const FInputActionValue& Value);
  void Look(const FInputActionValue& Value);
  void GetIn(const FInputActionValue& Value);

public:
  UFUNCTION(BlueprintCallable, Category = "Input")
  void DoMove(const FVector2D& MoveValue);

  UFUNCTION(BlueprintCallable, Category = "Input")
  void DoLook(const FVector2D& LookValue);

  UFUNCTION(BlueprintCallable, Category = "Input")
  void DoGetIn();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
