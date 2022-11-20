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
	void StartPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> ObjectiveWidget = nullptr;
};
