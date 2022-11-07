// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLogComponent.h"

// Sets default values for this component's properties
UCustomLogComponent::UCustomLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Error, TEXT("This is called when UCustomLogComponent is created."));
}


// Called when the game starts
void UCustomLogComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("This is called when the game starts. Message: %s"), *DataString);
}


// Called every frame
void UCustomLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
