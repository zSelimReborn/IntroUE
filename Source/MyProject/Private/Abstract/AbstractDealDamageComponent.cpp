// Fill out your copyright notice in the Description page of Project Settings.


#include "Abstract/AbstractDealDamageComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Components/ShapeComponent.h"

// Sets default values for this component's properties
UAbstractDealDamageComponent::UAbstractDealDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbstractDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
}

void UAbstractDealDamageComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() == OtherActor)
	{
		return;
	}

	OverlappingActor = OtherActor;
}

void UAbstractDealDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ResetOverlappingActor();
}

void UAbstractDealDamageComponent::PrepareTrigger()
{
	TriggerComponent = GetOwner()->FindComponentByClass<UShapeComponent>();
	if (TriggerComponent)
	{
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &UAbstractDealDamageComponent::OnOverlapStart);
		TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &UAbstractDealDamageComponent::OnOverlapEnd);
	}
}


void UAbstractDealDamageComponent::SetShouldDealDamage(const bool ShouldDealDamage)
{
	bShouldDealDamage = ShouldDealDamage;
}

// Called every frame
void UAbstractDealDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbstractDealDamageComponent::ApplyDamage(const float& Damage)
{
	if (OverlappingActor)
	{
		UGameplayStatics::ApplyDamage(
			OverlappingActor,
			Damage,
			nullptr,
			nullptr,
			UDamageType::StaticClass()
		);
	}
}

