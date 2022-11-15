// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "Components/StaticMeshComponent.h"
#include "DoorInteractionComponent.h"
#include "Components/BoxComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	SetRootComponent(DoorFrameComponent);

	DoorMainComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMainMesh"));
	DoorMainComponent->SetupAttachment(DoorFrameComponent);

	OpenerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OpenerBoxComponent"));
	OpenerBoxComponent->SetupAttachment(DoorFrameComponent);

	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteractionComponent"));
}

void AInteractableDoor::RotateDoor(const float Degrees) const
{
	const FRotator YawRotation{0.f, Degrees, 0.f};
	DoorMainComponent->SetRelativeRotation(YawRotation);
}

