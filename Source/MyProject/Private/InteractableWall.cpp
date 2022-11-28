// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWall.h"

#include "WallInteractionComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableWall::AInteractableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComponent"));
	
	WallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	WallMeshComponent->SetupAttachment(MainComponent);

	TriggerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMeshComponent"));
	TriggerMeshComponent->SetupAttachment(MainComponent);

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	TriggerBoxComponent->SetupAttachment(MainComponent);

	WallInteractionComponent = CreateDefaultSubobject<UWallInteractionComponent>(TEXT("WallInteractionComponent"));
}

// Called when the game starts or when spawned
void AInteractableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableWall::MoveWall(float ZOffset) const
{
	const FVector CurrentRelativeLocation = WallMeshComponent->GetRelativeLocation();
	WallMeshComponent->SetRelativeLocation(FVector{CurrentRelativeLocation.X, CurrentRelativeLocation.Y, ZOffset});
}

void AInteractableWall::MovePressurePlate(float ZOffset) const
{
	const FVector CurrentRelativeLocation = TriggerMeshComponent->GetRelativeLocation();
	TriggerMeshComponent->SetRelativeLocation(FVector{CurrentRelativeLocation.X, CurrentRelativeLocation.Y, ZOffset});
}

