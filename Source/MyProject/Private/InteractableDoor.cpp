// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "Components/StaticMeshComponent.h"
#include "DoorInteractionComponent.h"
#include "ObjectiveComponent.h"
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
	ObjectiveComponent = CreateDefaultSubobject<UObjectiveComponent>(TEXT("ObjectiveComponent"));

	DoorInteractionComponent->OnOpened().AddUObject(this, &AInteractableDoor::OnOpenDoor);
}

void AInteractableDoor::RotateDoor(const float Degrees) const
{
	const FRotator YawRotation{0.f, Degrees, 0.f};
	DoorMainComponent->SetRelativeRotation(YawRotation);
}

void AInteractableDoor::SetObjectiveCompleted()
{
	ObjectiveComponent->SetObjectiveCompleted();
}

void AInteractableDoor::SetObjectiveActive()
{
	ObjectiveComponent->SetObjectiveActive();
}

void AInteractableDoor::SetObjectiveInactive()
{
	ObjectiveComponent->SetObjectiveInactive();
}

bool AInteractableDoor::IsObjectiveCompleted() const
{
	return ObjectiveComponent->IsObjectiveCompleted();
}

bool AInteractableDoor::IsObjectiveActive() const
{
	return ObjectiveComponent->IsObjectiveActive();
}

bool AInteractableDoor::IsObjectiveInactive() const
{
	return ObjectiveComponent->IsObjectiveInactive();
}

void AInteractableDoor::OnOpenDoor()
{
	SetObjectiveCompleted();
}

