// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponent.h"
#include "PickupItemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPickupItemComponent : public UInteractionComponent
{
	GENERATED_BODY()

protected:
	virtual void InteractionStart() override;

	void AddItemToActor(AActor*) const;

protected:
	UPROPERTY(EditAnywhere, Category="Pickup Item")
	bool bDestroyOnPickup = true;
};
