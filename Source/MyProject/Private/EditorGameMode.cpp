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
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}

	UCheckpointSubsystem* CheckpointSubsystem = GetGameInstance()->GetSubsystem<UCheckpointSubsystem>();
	if (CheckpointSubsystem)
	{
		CheckpointSubsystem->LoadCheckpoints();
	}
}
