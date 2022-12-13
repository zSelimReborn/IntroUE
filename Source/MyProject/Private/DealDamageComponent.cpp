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

void UDealDamageComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapStart(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ApplyDamage(Damage);
}

// Called every frame
void UDealDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDealDamageComponent::SetShouldDealDamage(const bool bCond)
{
	Super::SetShouldDealDamage(bCond);

	if (ShouldDealDamage())
	{
		ApplyDamage(Damage);
	}
}

