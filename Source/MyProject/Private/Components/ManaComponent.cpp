// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ManaComponent.h"

static TAutoConsoleVariable<bool> CVarManaComponent(
	TEXT("MyProject.Components.UManaComponent.Debug"),
	false,
	TEXT("Toggle debugging for mana component."),
	ECVF_Default
);

// Sets default values for this component's properties
UManaComponent::UManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UManaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentMana = MaxMana;
	StartRestoreManaTimer();
}

void UManaComponent::StartRestoreManaTimer()
{
	GetOwner()->GetWorldTimerManager().SetTimer(RestoreManaTimer, this, &UManaComponent::OnEndRestoreManaTimer, RestoreSeconds, true);
}

void UManaComponent::OnEndRestoreManaTimer()
{
	RestoreMana(RestoreManaPerSeconds);
}

void UManaComponent::RestoreMana(const float& Amount)
{
	CurrentMana = FMath::Min(CurrentMana + Amount, MaxMana);
}

void UManaComponent::DebugDraw() const
{
	if (CVarManaComponent->GetBool())
	{
		const FVector ManaOffset{0.f, 0.f, -10.f};
		const FString ManaAsString = TEXT("Mana: ") + FString::SanitizeFloat(CurrentMana);
		
		DrawDebugString(GetWorld(), ManaOffset, ManaAsString, GetOwner(), FColor::Emerald, 0.f);
	}
}


// Called every frame
void UManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DebugDraw();
}

void UManaComponent::UseMana(const float& Amount)
{
	CurrentMana = FMath::Clamp(CurrentMana - Amount, 0.f, MaxMana);
}

void UManaComponent::FillMana(const float& Amount)
{
	RestoreMana(Amount);
}

