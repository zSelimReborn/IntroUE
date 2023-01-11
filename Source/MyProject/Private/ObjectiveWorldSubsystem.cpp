// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"

#include "EditorGameMode.h"
#include "ObjectiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widgets/ObjectiveHud.h"

void UObjectiveWorldSubsystem::OnObjectiveCompleted()
{
	CurrentObjectiveIndex = CurrentObjectiveIndex + 1;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* Objective)
{
	const size_t ObjectiveCount = Objectives.Num();
	Objectives.AddUnique(Objective);

	if (ObjectiveCount < Objectives.Num())
	{
		Objective->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* Objective)
{
	Objectives.Remove(Objective);
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* Objective, EObjectiveState CurrentState)
{
	if (Objective->IsObjectiveCompleted())
	{
		OnObjectiveCompleted();
	}

	if (HasCompletedAllObjectives())
	{
		ShowQuestCompletedWidget();
		OnAllObjectivesCompleted.Broadcast();
	}
	ShowCurrentObjectiveWidget();
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	const UObjectiveComponent* ActiveObjective = GetCurrentObjective();
	FString ObjectiveAsString = (ActiveObjective)? ActiveObjective->GetDescription() : "";
	
	return (!ObjectiveAsString.IsEmpty())? ObjectiveAsString : TEXT("N/A");
}

int8 UObjectiveWorldSubsystem::GetNumObjectivesCompleted() const
{
	int8 NumObjectivesCompleted = 0;
	for (const auto Objective : Objectives)
	{
		if (Objective->IsObjectiveCompleted())
		{
			NumObjectivesCompleted++;
		}
	}

	return NumObjectivesCompleted;
}

bool UObjectiveWorldSubsystem::HasObjectivesActive() const
{
	for (const auto Objective : Objectives)
	{
		if (Objective->IsObjectiveActive())
		{
			return true;
		}
	}

	return false;
}

bool UObjectiveWorldSubsystem::HasCompletedAllObjectives() const
{
	return GetNumObjectivesCompleted() >= Objectives.Num();
}

UObjectiveComponent* UObjectiveWorldSubsystem::GetCurrentObjective()
{
	if (Objectives.IsValidIndex(CurrentObjectiveIndex))
	{
		return Objectives[CurrentObjectiveIndex];
	}

	return nullptr;
}

void UObjectiveWorldSubsystem::OnMapStart()
{
	CreateWidgetInstances();
	ShowCurrentObjectiveWidget();
}

void UObjectiveWorldSubsystem::CreateWidgetInstances()
{
	AEditorGameMode* GameMode = Cast<AEditorGameMode>(GetWorld()->GetAuthGameMode());
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (GameMode && PlayerController)
	{
		ObjectiveWidget = CreateWidget<UObjectiveHud>(PlayerController, GameMode->ObjectiveWidgetClass);
		QuestCompletedWidgetInstance = CreateWidget<UUserWidget>(PlayerController, GameMode->QuestCompletedWidgetClass);
	}
}

void UObjectiveWorldSubsystem::ShowCurrentObjectiveWidget()
{
	if (ObjectiveWidget && !ObjectiveWidget->IsInViewport())
	{
		ObjectiveWidget->AddToViewport();
	}

	if (ObjectiveWidget)
	{
		if (!HasCompletedAllObjectives())
		{
			ObjectiveWidget->UpdateCurrentObjectiveText(GetCurrentObjectiveDescription());
		}
		ObjectiveWidget->UpdateObjectiveCount(GetNumObjectivesCompleted(), Objectives.Num());
	}

	if (Objectives.Num() <= 0)
	{
		HideCurrentObjectiveWidget();
	}
}

void UObjectiveWorldSubsystem::HideCurrentObjectiveWidget()
{
	if (ObjectiveWidget && ObjectiveWidget->IsInViewport())
	{
		ObjectiveWidget->RemoveFromViewport();
	}
}

void UObjectiveWorldSubsystem::ShowQuestCompletedWidget()
{
	if (QuestCompletedWidgetInstance && !QuestCompletedWidgetInstance->IsInViewport())
	{
		QuestCompletedWidgetInstance->AddToViewport();
	}
}

void UObjectiveWorldSubsystem::HideQuestCompletedWidget()
{
	if (QuestCompletedWidgetInstance && QuestCompletedWidgetInstance->IsInViewport())
	{
		QuestCompletedWidgetInstance->RemoveFromViewport();
	}
}
