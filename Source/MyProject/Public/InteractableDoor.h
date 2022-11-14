// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"


class UDoorInteractionComponent;
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

public:
	AInteractableDoor();
protected:
	UPROPERTY(EditAnywhere, NoClear)
	UStaticMeshComponent* DoorMainComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;
};
