// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "BaseCharacter.h"
#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
	PrepareInteractionEvent();
}

void UInteractionComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		InteractingActor = OtherActor;
	}
}

void UInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractingActor = nullptr;
}


void UInteractionComponent::PrepareTrigger()
{
	UShapeComponent* ParentVolume = GetOwner()->FindComponentByClass<UShapeComponent>();
	if (ParentVolume)
	{
		ParentVolume->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapStart);
		ParentVolume->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapEnd);
	}
}

void UInteractionComponent::PrepareInteractionEvent()
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->OnPlayerInteractStart.AddUObject(this, &UInteractionComponent::InteractionStart);
	}
}

void UInteractionComponent::InteractionStart()
{
	// Override by children classes
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

