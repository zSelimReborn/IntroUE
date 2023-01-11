// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ObjectiveHud.h"

#include "Components/TextBlock.h"

void UObjectiveHud::UpdateCurrentObjectiveText(const FString& Content)
{
	CurrentObjectiveText->SetText(FText::FromString(Content));
}

void UObjectiveHud::UpdateObjectiveCount(const uint8& ObjectivesCompleted, const uint8& TotalObjectives)
{
	ObjectivesCountText->SetText(FText::Format(FTextFormat::FromString("{0} / {1}"), ObjectivesCompleted, TotalObjectives));
}
