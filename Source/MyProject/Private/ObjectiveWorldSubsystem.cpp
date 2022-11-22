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
	DisplayObjectiveWidget();
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
	DisplayObjectiveWidget();
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	const UObjectiveComponent* ActiveObjective = GetActiveObjective();
	FString ObjectiveAsString = (ActiveObjective)? ActiveObjective->GetDescription() + " New!" : "";
	for (const UObjectiveComponent* Objective : Objectives)
	{
		if (Objective->IsObjectiveCompleted())
		{
			ObjectiveAsString += "\n ";
			ObjectiveAsString += Objective->GetDescription();
			ObjectiveAsString += " Completed.";
		}
	}
	
	return (!ObjectiveAsString.IsEmpty())? ObjectiveAsString : TEXT("N/A");
}

UObjectiveComponent* UObjectiveWorldSubsystem::GetActiveObjective()
{
	for (UObjectiveComponent* Objective : Objectives)
	{
		if (Objective->IsObjectiveActive())
		{
			return Objective;
		}
	}

	return nullptr;
}
