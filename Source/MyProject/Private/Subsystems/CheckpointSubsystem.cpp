// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CheckpointSubsystem.h"

#include "BaseCharacter.h"
#include "Checkpoint.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

UCheckpointSubsystem::UCheckpointSubsystem() :
	UGameInstanceSubsystem()
{
	
}

bool UCheckpointSubsystem::ShouldRespawnOnCheckpoint()
{
	return (CurrentCheckpoint != nullptr);
}

FTransform UCheckpointSubsystem::GetRespawnCheckpointTransform() const
{
	const FVector RespawnLocation {0.f, 0.f, 0.f};
	FTransform RespawnTransform{RespawnLocation};
	if (CurrentCheckpoint)
	{
		RespawnTransform = CurrentCheckpoint->GetRespawnTransform();
	}

	return RespawnTransform;
}


void UCheckpointSubsystem::LoadCheckpoints()
{
	TArray<AActor*> TempCheckpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint::StaticClass(), TempCheckpoints);

	for (AActor* TempCheckpoint : TempCheckpoints)
	{
		ACheckpoint* Checkpoint = Cast<ACheckpoint>(TempCheckpoint);
		if (Checkpoint)
		{
			Checkpoints.Add(Checkpoint);

			Checkpoint->OnEnterCheckpoint().AddUObject(this, &UCheckpointSubsystem::OnEnterCheckpoint);
			Checkpoint->OnLeaveCheckpoint().AddUObject(this, &UCheckpointSubsystem::OnLeaveCheckpoint);
		}
	}

	SetupPlayerDeathEvent();
}

void UCheckpointSubsystem::OnEnterCheckpoint(ACheckpoint* Checkpoint)
{
	UE_LOG(LogTemp, Error, TEXT("Enter checkpoint area"));
	CurrentCheckpoint = Checkpoint;
}

void UCheckpointSubsystem::OnLeaveCheckpoint(ACheckpoint* Checkpoint)
{
	UE_LOG(LogTemp, Error, TEXT("Leave checkpoint area"));
	LastCheckpoint = CurrentCheckpoint;
	CurrentCheckpoint = nullptr;
}

void UCheckpointSubsystem::OnDeathPlayer(bool FellOutOfWorld)
{
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* Pawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);;

	FTransform RespawnTransform = GetRespawnCheckpointTransform();
	const bool bShouldRespawnOnCheckpoint = ShouldRespawnOnCheckpoint();
	
	if (FellOutOfWorld && LastCheckpoint)
	{
		RespawnTransform = LastCheckpoint->GetRespawnTransform();
	}

	if (Pawn)
	{
		Pawn->Destroy();
	}
	
	if (GameMode)
	{
		if (bShouldRespawnOnCheckpoint)
		{
			GameMode->RestartPlayerAtTransform(PlayerController, RespawnTransform);
		} else
		{
			GameMode->RestartPlayer(PlayerController);
		}
	}
	else
	{
		PlayerController->RestartLevel();
	}

	SetupPlayerDeathEvent();
}

void UCheckpointSubsystem::SetupPlayerDeathEvent()
{
	APawn* Pawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);;
	ABaseCharacter* Player = Cast<ABaseCharacter>(Pawn);
	if (Player)
	{
		if (!Player->OnDeathPlayer().IsBoundToObject(this))
		{
			Player->OnDeathPlayer().AddUObject(this, &UCheckpointSubsystem::OnDeathPlayer);
		}
	}
}
