// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallInteractionComponent.generated.h"

class UBoxComponent;
class AInteractableWall;

UENUM()
enum class EWallState : uint8
{
	Closed		UMETA(DisplayName="Closed"),
	Opened		UMETA(DisplayName="Opened"),
	Opening		UMETA(DisplayName="Opening"),
	
	Max			UMETA(DisplayName="MAX")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UWallInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float DesiredZOffset = 100.f;

	UPROPERTY(EditAnywhere)
	float TimeToMove = 1.f;

	float CurrentOpeningTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWallState WallState = EWallState::Closed;

	UPROPERTY(Transient)
	TObjectPtr<APawn> Player = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<AInteractableWall> Wall = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PerformMove(const float DeltaTime);
	void ClosePressurePlate() const;

	FORCEINLINE EWallState GetWallState() const { return WallState; }
	FORCEINLINE bool IsOpened() const { return WallState == EWallState::Opened; }
	FORCEINLINE bool IsClosed() const { return WallState == EWallState::Closed; }
	FORCEINLINE bool IsOpening() const { return WallState == EWallState::Opening; }
	FORCEINLINE bool IsRotating() const { return (!IsOpened() && !IsClosed()); }

private:
	FORCEINLINE void SetOpened() { WallState = EWallState::Opened; }
	FORCEINLINE void SetClosed() { WallState = EWallState::Closed; }
	FORCEINLINE void SetOpening() { WallState = EWallState::Opening; }

};
