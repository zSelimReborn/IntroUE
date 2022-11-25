// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ObjectiveComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<UUserWidget>);
	void DisplayObjectiveWidget();

	void OnObjectiveCompleted();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* Objective);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* Objective);

	void OnObjectiveStateChanged(UObjectiveComponent*, EObjectiveState);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UObjectiveComponent* GetCurrentObjective();
	
protected:
	UPROPERTY(Transient)
	UUserWidget* ObjectiveWidget;

	UPROPERTY(Transient)
	TArray<UObjectiveComponent*> Objectives;

	UPROPERTY(VisibleAnywhere)
	int CurrentObjectiveIndex = 0;
};
