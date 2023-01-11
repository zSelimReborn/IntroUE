// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"

class UObjectiveWorldSubsystem;

UENUM()
enum class EObjectiveState
{
	Inactive	UMETA(DisplayName = "Inactive"),
	Active		UMETA(DisplayName = "Active"),
	Completed	UMETA(DisplayName = "Completed")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectiveComponent();

	DECLARE_EVENT_TwoParams(FObjectiveComponent, FStateChanged, UObjectiveComponent*, EObjectiveState);
	FStateChanged& OnStateChanged() { return StateChangedEvent; }
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void InitializeComponent() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ChangeState(const EObjectiveState&);
	
	FORCEINLINE EObjectiveState GetState() const { return State; };
	FORCEINLINE FString GetDescription() const { return Description; }
	
	FORCEINLINE void SetObjectiveInactive() { ChangeState(EObjectiveState::Inactive); }
	FORCEINLINE void SetObjectiveActive() { ChangeState(EObjectiveState::Active); }
	FORCEINLINE void SetObjectiveCompleted() { ChangeState(EObjectiveState::Completed); }

	FORCEINLINE bool IsObjectiveInactive() const { return GetState() == EObjectiveState::Inactive; }
	FORCEINLINE bool IsObjectiveActive() const { return GetState() == EObjectiveState::Active; }
	FORCEINLINE bool IsObjectiveCompleted() const { return GetState() == EObjectiveState::Completed; }

protected:
	FStateChanged StateChangedEvent;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	EObjectiveState State = EObjectiveState::Inactive;

	UPROPERTY(Transient)
	TObjectPtr<UObjectiveWorldSubsystem> ObjectiveWorldSubsystem;
};
