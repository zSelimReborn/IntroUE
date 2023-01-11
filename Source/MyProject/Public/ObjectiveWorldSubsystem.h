// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ObjectiveComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveWorldSubsystem.generated.h"

class UObjectiveHud;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllObjectivesCompleted);

/**
 * 
 */
UCLASS()
class MYPROJECT_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void OnObjectiveCompleted();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* Objective);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* Objective);

	void OnObjectiveStateChanged(UObjectiveComponent*, EObjectiveState);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	int8 GetNumObjectivesCompleted() const;

	bool HasObjectivesActive() const;
	bool HasCompletedAllObjectives() const;

	UObjectiveComponent* GetCurrentObjective();

	UFUNCTION(BlueprintCallable)
	void OnMapStart();

	FAllObjectivesCompleted OnAllObjectivesCompleted;
	
protected:
	virtual void CreateWidgetInstances();
	
	virtual void ShowCurrentObjectiveWidget();
	virtual void HideCurrentObjectiveWidget();

	virtual void ShowQuestCompletedWidget();
	virtual void HideQuestCompletedWidget();
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UObjectiveHud> ObjectiveWidget;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> QuestCompletedWidgetInstance;

	UPROPERTY(Transient)
	TArray<UObjectiveComponent*> Objectives;

	UPROPERTY(VisibleAnywhere)
	int CurrentObjectiveIndex = 0;
};
