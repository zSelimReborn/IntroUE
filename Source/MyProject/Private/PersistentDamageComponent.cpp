// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentDamageComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/ShapeComponent.h"

// Sets default values for this component's properties
UPersistentDamageComponent::UPersistentDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPersistentDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	PrepareTrigger();	
}

void UPersistentDamageComponent::PrepareTrigger()
{
	TriggerShape = GetOwner()->FindComponentByClass<UShapeComponent>();
	if (TriggerShape)
	{
		TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &UPersistentDamageComponent::OnOverlapStart);
		TriggerShape->OnComponentEndOverlap.AddDynamic(this, &UPersistentDamageComponent::OnOverlapEnd);
	}
}

void UPersistentDamageComponent::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
	{
		return;
	}

	OverlappingActor = OtherActor;
	SetDealingDamage();
}

void UPersistentDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetDefaultState();
	GetOwner()->GetWorldTimerManager().ClearTimer(DealerTimer);
	ResetOverlappingActor();
}


void UPersistentDamageComponent::RestartDamage()
{
	if (IsCoolingDown())
	{
		SetDealingDamage();
	}
}

void UPersistentDamageComponent::StartTimer()
{
	GetOwner()->GetWorldTimerManager().SetTimer(DealerTimer, this, &UPersistentDamageComponent::RestartDamage, Seconds, false);
}

// Called every frame
void UPersistentDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (CurrentState)
	{
	case EDealerDamageState::DealingDmg:
		ApplyDamage();
		StartTimer();
		SetCoolDown();
		break;
	case EDealerDamageState::CoolDown: break;
	case EDealerDamageState::Default: break;
	default: ;
	}
}

void UPersistentDamageComponent::ApplyDamage() const
{
	if (OverlappingActor)
	{
		UGameplayStatics::ApplyDamage(
			OverlappingActor,
			DamagePerSeconds,
			nullptr,
			nullptr,
			UDamageType::StaticClass()
		);
	}
}

