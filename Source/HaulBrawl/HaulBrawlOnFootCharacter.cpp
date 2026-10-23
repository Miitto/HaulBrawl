// Fill out your copyright notice in the Description page of Project Settings.

#include "HaulBrawlOnFootCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HaulBrawl.h"

// Sets default values
AHaulBrawlOnFootCharacter::AHaulBrawlOnFootCharacter() {
  GetMesh()->SetSimulatePhysics(true);
  GetMesh()->SetCollisionProfileName(FName("Vehicle"));

  CharacterMovement = CastChecked<UCharacterMovementComponent>(GetCharacterMovement());
}

// Called when the game starts or when spawned
void AHaulBrawlOnFootCharacter::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AHaulBrawlOnFootCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AHaulBrawlOnFootCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHaulBrawlOnFootCharacter::Move);
    EnhancedInputComponent->BindAction(GetInAction, ETriggerEvent::Triggered, this, &AHaulBrawlOnFootCharacter::GetIn);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHaulBrawlOnFootCharacter::Look);
  } else {
    UE_LOG(LogHaulBrawl, Error,
           TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend "
                "to use the legacy system, then you will need to update this C++ file."),
           *GetNameSafe(this));
  }
}

void AHaulBrawlOnFootCharacter::Move(const FInputActionValue& Value) {
  // route the input
  DoMove(Value.Get<FVector2D>());
}

void AHaulBrawlOnFootCharacter::Look(const FInputActionValue& Value) {
  // route the input
  DoLook(Value.Get<FVector2D>());
}

void AHaulBrawlOnFootCharacter::GetIn(const FInputActionValue& Value) {
  // route the input
  DoGetIn();
}

void AHaulBrawlOnFootCharacter::DoMove(const FVector2D& MoveValue) {
  // add movement in that direction
  AddMovementInput(GetActorForwardVector(), MoveValue.Y);
  AddMovementInput(GetActorRightVector(), MoveValue.X);
}

void AHaulBrawlOnFootCharacter::DoLook(const FVector2D& LookValue) {
  // add yaw and pitch input to the controller
  AddControllerYawInput(LookValue.X);
  AddControllerPitchInput(LookValue.Y);
}

void AHaulBrawlOnFootCharacter::DoGetIn() { UE_LOGF(LogHaulBrawl, Display, "Getting in vehicle"); }