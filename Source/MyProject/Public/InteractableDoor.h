// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IInteractable.h"
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
class MYPROJECT_API AInteractableDoor : public AActor, public IIInteractable
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

	virtual void Interact(APawn*) override;
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;
	
protected:
	ABaseCharacter* GetPlayer();
	void OnPlayerAddInventory(const FString&) const;

	void PrepareTrigger();
	
	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
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

	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<class UWidgetComponent> InteractWidgetComponent;
};
