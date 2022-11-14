// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "Components/StaticMeshComponent.h"
#include "DoorInteractionComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorMainComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMainMesh"));
	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteractionComponent"));

	SetRootComponent(DoorMainComponent);
	DoorMainComponent->SetupAttachment(GetRootComponent());
}

