// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeTrialGameMode.generated.h"

class ATimeTrialTrackGate;

/**
 *  A simple GameMode for a Time Trial racing game
 */
UCLASS(abstract)
class ATimeTrialGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	/** Actor tag used to find the finish line marker on the level */
	UPROPERTY(EditAnywhere, Category="Time Trial")
	FName FinishTag;

	/** Number of laps for the race */
	UPROPERTY(EditAnywhere, Category="Time Trial")
	int32 Laps = 3;

	/** Pointer to the finish line track marker */
	TObjectPtr<ATimeTrialTrackGate> FinishLineMarker;

protected:

	/** Determines how many local players should be spawned on game start */
	UPROPERTY(EditDefaultsOnly, Category="Local Multiplayer", meta = (ClampMin = 1, ClampMax = 4))
	int32 NumberOfLocalPlayers = 1;

	/** Used to assign players to different PlayerStarts in the level */
	int32 CurrentPlayerStartAssignment = 0;

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Assigns a PlayerStart to a specific player */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

public: 

	/** Returns the track marker for the finish line */
	ATimeTrialTrackGate* GetFinishLine() const;

	/** Returns the number of laps for the race */
	int32 GetLaps() const { return Laps; };

};
