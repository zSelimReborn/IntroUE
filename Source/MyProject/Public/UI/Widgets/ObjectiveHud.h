// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveHud.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UObjectiveHud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateCurrentObjectiveText(const FString&);
	virtual void UpdateObjectiveCount(const uint8& ObjectivesCompleted, const uint8& TotalObjectives);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentObjectiveText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ObjectivesCountText;
};
