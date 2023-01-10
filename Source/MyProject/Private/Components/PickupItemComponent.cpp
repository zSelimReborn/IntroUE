// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PickupItemComponent.h"

#include "BaseCharacter.h"

void UPickupItemComponent::InteractionStart()
{
	Super::InteractionStart();

	if (InteractingActor)
	{
		AddItemToActor(InteractingActor);
	}
}

void UPickupItemComponent::AddItemToActor(AActor* OtherActor) const
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player)
	{
		Player->AddKeyToInventory(GetNameSafe(GetOwner()));
		OnInteractionSuccess.Broadcast();
		
		if (bDestroyOnPickup)
		{
			GetOwner()->Destroy();
		}
	}
}
