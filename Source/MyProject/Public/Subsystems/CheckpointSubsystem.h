// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CheckpointSubsystem.generated.h"

class ACheckpoint;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UCheckpointSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCheckpointSubsystem();
	virtual bool ShouldRespawnOnCheckpoint();
	virtual FTransform GetRespawnCheckpointTransform() const;
	
	virtual void LoadCheckpoints();
	FORCEINLINE ACheckpoint* GetCurrentCheckpoint() const { return CurrentCheckpoint; }

protected:
	UFUNCTION()
	void OnEnterCheckpoint(ACheckpoint* Checkpoint);

	UFUNCTION()
	void OnLeaveCheckpoint(ACheckpoint* Checkpoint);

	UFUNCTION()
	void OnDeathPlayer(bool FellOutOfWorld);

	void SetupPlayerDeathEvent();
	
protected:
	UPROPERTY(VisibleAnywhere, Transient)
	TArray<ACheckpoint*> Checkpoints;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<ACheckpoint> CurrentCheckpoint;
	
	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<ACheckpoint> LastCheckpoint;
};
