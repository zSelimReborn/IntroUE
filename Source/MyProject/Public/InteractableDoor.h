// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"


class UDoorInteractionComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UObjectiveComponent;
class ABaseCharacter;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

public:
	AInteractableDoor();
	virtual void BeginPlay() override;

	void RotateDoor(const float Degrees) const;
	
	void SetOpenDoorObjectiveCompleted() const;
	void SetOpenDoorObjectiveActive() const;
	void SetOpenDoorObjectiveInactive() const;

	void SetPickupKeyObjectiveCompleted() const;
	void SetPickupKeyObjectiveActive() const;
	void SetPickupKeyObjectiveInactive() const;

	bool IsOpenDoorObjectiveCompleted() const;
	bool IsOpenDoorObjectiveActive() const;
	bool IsOpenDoorObjectiveInactive() const;

	bool IsPickupKeyObjectiveCompleted() const;
	bool IsPickupKeyObjectiveActive() const;
	bool IsPickupKeyObjectiveInactive() const;

	void OnOpenDoor() const;

	FVector GetMeshCenter() const;

protected:
	ABaseCharacter* GetPlayer();
	void OnPlayerAddInventory(const FString&) const;
	
protected:
	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* DoorMainComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* DoorFrameComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UBoxComponent* OpenerBoxComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;

	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UObjectiveComponent> PickupKeyObjective;
	
	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UObjectiveComponent> OpenDoorObjective;
};
