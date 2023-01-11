// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EditorGameMode.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEditorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

protected:
	UFUNCTION()
	virtual void OnQuestCompleted();

	void FireRestartLevel() const;
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Objective Widgets")
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Objective Widgets")
	TSubclassOf<UUserWidget> QuestCompletedWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	int8 RestartLevelTimeAfterQuestCompleted = 5.f;
	
	FTimerHandle RestartLevelHandler;
};
