// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AEditorGameMode::StartPlay()
{
	Super::StartPlay();

	if (ObjectiveWidgetClass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
	
	if(ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}
}
