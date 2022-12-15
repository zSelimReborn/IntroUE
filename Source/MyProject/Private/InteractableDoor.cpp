// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "DoorInteractionComponent.h"
#include "ObjectiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	SetRootComponent(DoorFrameComponent);

	DoorMainComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMainMesh"));
	DoorMainComponent->SetupAttachment(DoorFrameComponent);

	OpenerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OpenerBoxComponent"));
	OpenerBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OpenerBoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OpenerBoxComponent->SetupAttachment(DoorFrameComponent);

	InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget Component"));
	InteractWidgetComponent->SetupAttachment(DoorFrameComponent);

	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("DoorInteractionComponent"));
	PickupKeyObjective = CreateDefaultSubobject<UObjectiveComponent>(TEXT("PickupKeyObjective"));
	OpenDoorObjective = CreateDefaultSubobject<UObjectiveComponent>(TEXT("OpenDoorObjective"));

	DoorInteractionComponent->OnOpened().AddUObject(this, &AInteractableDoor::OnOpenDoor);
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
	HideInteractWidget();
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

void AInteractableDoor::Interact(APawn* Player)
{
	// Open or close the door
	DoorInteractionComponent->ToggleDoor();
}

void AInteractableDoor::ShowInteractWidget()
{
	if (InteractWidgetComponent)
	{
		InteractWidgetComponent->SetVisibility(true);
	}
}

void AInteractableDoor::HideInteractWidget()
{
	if (InteractWidgetComponent)
	{
		InteractWidgetComponent->SetVisibility(false);
	}
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

void AInteractableDoor::PrepareTrigger()
{
	OpenerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableDoor::OnOverlapStart);
	OpenerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractableDoor::OnOverlapEnd);
}

void AInteractableDoor::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}

	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player)
	{
		ShowInteractWidget();
		Player->SetInteractableOverlappingActor(this);
	}
}

void AInteractableDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
	{
		return;
	}

	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player)
	{
		HideInteractWidget();
		Player->ResetInteractableOverlappingActor(this);
	}
}

