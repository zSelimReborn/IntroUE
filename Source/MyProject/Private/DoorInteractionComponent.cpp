// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = StartRotation + DesiredRotation;
	CurrentRotationTime = 0.f;
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRotationTime < TimeToRotate)
	{
		CurrentRotationTime += DeltaTime;
		UE_LOG(LogTemp, Error, TEXT("CurrentRotationTime: %.2f - DeltaTime: %.2f"), CurrentRotationTime, DeltaTime);
		const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.f, 1.f);
		UE_LOG(LogTemp, Error, TEXT("Rotation Alpha: %.2f"), RotationAlpha);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
}

