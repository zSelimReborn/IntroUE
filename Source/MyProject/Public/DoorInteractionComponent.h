// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Components/InteractionComponent.h"
#include "DoorInteractionComponent.generated.h"

UENUM()
enum class EDoorState : uint8
{
	Closed		UMETA(DisplayName="Closed"),
	Opened		UMETA(DisplayName="Opened"),
	Opening		UMETA(DisplayName="Opening"),
	Closing		UMETA(DisplayName="Closing"),
	
	Max			UMETA(DisplayName="MAX")
};

UENUM()
enum class EDoorTypeForward
{
	Forward UMETA(DisplayName="Forward Vector"),
	Right UMETA(DisplayName="Right Vector")
};

class UBoxComponent;
class AInteractableDoor;
class ABaseKey;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Setup for events
	DECLARE_EVENT(FDoorInteractionComponent, FOpened);
	DECLARE_EVENT(FDoorInteractionComponent, FClosed);
	
	FOpened& OnOpened() { return OpenedEvent; }
	FOpened OpenedEvent;

	FClosed& OnClosed() { return ClosedEvent; }
	FClosed ClosedEvent;

	void ToggleDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InteractionStart() override;

	UPROPERTY(EditAnywhere)
	float DesiredYawRotation = 0.f;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.f;

	float CurrentRotationTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* OpenerTrigger;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;

	UPROPERTY(EditAnywhere)
	float PlayerFOVDegrees = 45.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDoorState DoorState = EDoorState::Closed;

	UPROPERTY(EditAnywhere)
	EDoorTypeForward TypeForward = EDoorTypeForward::Forward;

	UPROPERTY(EditAnywhere)
	float DoorSize = 100.f;

	UPROPERTY(Transient)
	APawn* Player = nullptr;

	UPROPERTY(Transient)
	AInteractableDoor* Door = nullptr;

	UPROPERTY(Transient)
	FString KeyToOpenName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ABaseKey> KeyToOpen;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE EDoorState GetDoorState() const { return DoorState; }
	FORCEINLINE bool IsOpened() const { return DoorState == EDoorState::Opened; }
	FORCEINLINE bool IsClosed() const { return DoorState == EDoorState::Closed; }
	FORCEINLINE bool IsOpening() const { return DoorState == EDoorState::Opening; }
	FORCEINLINE bool IsClosing() const { return DoorState == EDoorState::Closing; }
	FORCEINLINE bool IsRotating() const { return (!IsOpened() && !IsClosed()); }

	FVector GetActorForwardVector() const;

	bool CanOpenDoor() const;
	bool IsDoorBlocked() const;

	FORCEINLINE FString GetKeyToOpenName() const { return KeyToOpenName; };

protected:
	virtual float GetAngleBetweenVectors(FVector, FVector);
	virtual bool IsPlayerLookingAtDoor(const APawn*);
	virtual bool IsPlayerBehindDoor(const APawn*);

	virtual void PerformRotation(const float);

	static void OnDebugToggled(IConsoleVariable*);
	void DebugDraw() const;

private:
	FORCEINLINE void SetOpened() { DoorState = EDoorState::Opened; }
	FORCEINLINE void SetClosed() { DoorState = EDoorState::Closed; }
	FORCEINLINE void SetOpening() { DoorState = EDoorState::Opening; }
	FORCEINLINE void SetClosing() { DoorState = EDoorState::Closing; } 
};
