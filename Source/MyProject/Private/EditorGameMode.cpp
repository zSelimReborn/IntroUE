// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorGameMode.h"

#include "ObjectiveWorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/CheckpointSubsystem.h"

void AEditorGameMode::StartPlay()
{
	Super::StartPlay();

	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->OnAllObjectivesCompleted.AddDynamic(this, &AEditorGameMode::OnQuestCompleted);
	}
	
	UCheckpointSubsystem* CheckpointSubsystem = GetGameInstance()->GetSubsystem<UCheckpointSubsystem>();
	if (CheckpointSubsystem)
	{
		CheckpointSubsystem->LoadCheckpoints();
	}
}

void AEditorGameMode::OnQuestCompleted()
{
	GetWorldTimerManager().SetTimer(RestartLevelHandler, this, &AEditorGameMode::FireRestartLevel, RestartLevelTimeAfterQuestCompleted, false);
}

void AEditorGameMode::FireRestartLevel() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}
