// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"


class UDoorInteractionComponent;
class UStaticMeshComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

public:
	AInteractableDoor();

	void RotateDoor(const float Degrees) const;
	
protected:
	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* DoorMainComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* DoorFrameComponent;

	UPROPERTY(EditAnywhere, NoClear)
	UBoxComponent* OpenerBoxComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;
};
