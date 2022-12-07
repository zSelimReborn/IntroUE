// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamageComponent.h"

#include "Components/ShapeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDealDamageComponent::UDealDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
}

void UDealDamageComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("UDealDamageComponent::OnOverlapStart called."));

	if (OtherActor == GetOwner())
	{
		return;
	}
	
	UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			nullptr,
			nullptr,
			UDamageType::StaticClass()
		);
}


void UDealDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("UDealDamageComponent::OnOverlapEnd called."));
}

void UDealDamageComponent::PrepareTrigger()
{
	TriggerComponent = GetOwner()->FindComponentByClass<UShapeComponent>();
	if (TriggerComponent)
	{
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapStart);
		TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapEnd);
	}
}

// Called every frame
void UDealDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

