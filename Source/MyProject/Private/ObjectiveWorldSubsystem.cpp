// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"

#include "ObjectiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget(PlayerController, ObjectiveWidgetClass);
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr."));
	ObjectiveWidget->AddToViewport();
}

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
	
	DisplayObjectiveWidget();
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	const UObjectiveComponent* ActiveObjective = GetCurrentObjective();
	FString ObjectiveAsString = (ActiveObjective)? ActiveObjective->GetDescription() + " New!" : "";

	if (Objectives.IsValidIndex(CurrentObjectiveIndex - 1))
	{
		const UObjectiveComponent* LastObjective = Objectives[CurrentObjectiveIndex - 1];
		if (LastObjective->IsObjectiveCompleted())
		{
			ObjectiveAsString += "\n ";
			ObjectiveAsString += LastObjective->GetDescription();
			ObjectiveAsString += " Completed.";
		}
	}
	
	return (!ObjectiveAsString.IsEmpty())? ObjectiveAsString : TEXT("N/A");
}

UObjectiveComponent* UObjectiveWorldSubsystem::GetCurrentObjective()
{
	if (Objectives.IsValidIndex(CurrentObjectiveIndex))
	{
		return Objectives[CurrentObjectiveIndex];
	}

	return nullptr;
}
