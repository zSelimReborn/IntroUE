// Fill out your copyright notice in the Description page of Project Settings.


#include "HealComponent.h"

#include "BaseCharacter.h"
#include "Components/ShapeComponent.h"

// Sets default values for this component's properties
UHealComponent::UHealComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();
}

void UHealComponent::PrepareTrigger()
{
	TriggerShape = GetOwner()->FindComponentByClass<UShapeComponent>();
	if (TriggerShape)
	{
		TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &UHealComponent::OnOverlapStart);
	}
}

void UHealComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
	{
		return;
	}

	ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}

	Player->RegenHealth(HealQty);
	if (bDestroyOnHeal)
	{
		GetOwner()->Destroy();
	}
}


// Called every frame
void UHealComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

