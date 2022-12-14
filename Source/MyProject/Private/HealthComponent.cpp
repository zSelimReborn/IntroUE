// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BaseCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarHealthComponent(
	TEXT("MyProject.HealthComponent.Debug"),
	false,
	TEXT("Toggle debugging for health component."),
	ECVF_Default
);

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
	Player = Cast<ABaseCharacter>(GetOwner());
	SetupOnDamageDelegate();
}

void UHealthComponent::OnDeath()
{
	if (Player)
	{
		Player->OnDeath(false);
	}
}

void UHealthComponent::SetupOnDamageDelegate()
{
	if (Player)
	{
		Player->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	}
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	TakeDamage(Damage);
}

void UHealthComponent::DebugDraw() const
{
	if (CVarHealthComponent->GetBool())
	{
		const FVector HealthOffset{0.f, 0.f, 0.f};
		const FString HealthAsString = TEXT("Health: ") + FString::SanitizeFloat(CurrentHealth);
		DrawDebugString(GetWorld(), HealthOffset, HealthAsString, GetOwner(), FColor::Red, 0.f);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DebugDraw();
}

void UHealthComponent::TakeDamage(const float& Damage)
{
	if (Damage <= 0.f || IsDead())
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	if (IsDead())
	{
		OnDeath();
	}
}

void UHealthComponent::RestoreHealth(const float& Regen)
{
	if (Regen <= 0.f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + Regen, 0.f, MaxHealth);
}

