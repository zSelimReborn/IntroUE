// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "BaseCharacter.h"
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
	PickupKeyObjective = CreateDefaultSubobject<UObjectiveComponent>(TEXT("PickupKeyObjective"));
	OpenDoorObjective = CreateDefaultSubobject<UObjectiveComponent>(TEXT("OpenDoorObjective"));

	DoorInteractionComponent->OnOpened().AddUObject(this, &AInteractableDoor::OnOpenDoor);
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	if (ABaseCharacter* Player = GetPlayer())
	{
		Player->OnAddInventory().AddUObject(this, &AInteractableDoor::OnPlayerAddInventory);
	}
}

void AInteractableDoor::RotateDoor(const float Degrees) const
{
	const FRotator YawRotation{0.f, Degrees, 0.f};
	DoorMainComponent->SetRelativeRotation(YawRotation);
}

void AInteractableDoor::SetOpenDoorObjectiveCompleted() const
{
	OpenDoorObjective->SetObjectiveCompleted();
}

void AInteractableDoor::SetOpenDoorObjectiveActive() const
{
	OpenDoorObjective->SetObjectiveActive();
}

void AInteractableDoor::SetOpenDoorObjectiveInactive() const
{
	OpenDoorObjective->SetObjectiveInactive();
}

void AInteractableDoor::SetPickupKeyObjectiveCompleted() const
{
	PickupKeyObjective->SetObjectiveCompleted();
}

void AInteractableDoor::SetPickupKeyObjectiveActive() const
{
	PickupKeyObjective->SetObjectiveActive();
}

void AInteractableDoor::SetPickupKeyObjectiveInactive() const
{
	PickupKeyObjective->SetObjectiveInactive();
}

bool AInteractableDoor::IsOpenDoorObjectiveCompleted() const
{
	return OpenDoorObjective->IsObjectiveCompleted();
}

bool AInteractableDoor::IsOpenDoorObjectiveActive() const
{
	return OpenDoorObjective->IsObjectiveActive();
}

bool AInteractableDoor::IsOpenDoorObjectiveInactive() const
{
	return OpenDoorObjective->IsObjectiveInactive();
}

bool AInteractableDoor::IsPickupKeyObjectiveCompleted() const
{
	return PickupKeyObjective->IsObjectiveCompleted();
}

bool AInteractableDoor::IsPickupKeyObjectiveActive() const
{
	return PickupKeyObjective->IsObjectiveActive();
}

bool AInteractableDoor::IsPickupKeyObjectiveInactive() const
{
	return PickupKeyObjective->IsObjectiveInactive();
}

void AInteractableDoor::OnOpenDoor() const
{
	SetOpenDoorObjectiveCompleted();
}

FVector AInteractableDoor::GetMeshCenter() const
{
	FVector Origin;
	FVector BoxExtent;

	GetActorBounds(true, Origin, BoxExtent, false);
	return Origin;
}

ABaseCharacter* AInteractableDoor::GetPlayer()
{
	APawn* Pawn = (GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())? GetWorld()->GetFirstPlayerController()->GetPawn() : nullptr;
	return Cast<ABaseCharacter>(Pawn);
}

void AInteractableDoor::OnPlayerAddInventory(const FString& ItemName) const
{
	if (DoorInteractionComponent->GetKeyToOpenName().Equals(ItemName))
	{
		SetPickupKeyObjectiveCompleted();
	}
}

