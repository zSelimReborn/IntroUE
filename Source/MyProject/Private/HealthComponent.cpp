// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
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

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(const float& Damage)
{
	UE_LOG(LogTemp, Error, TEXT("UHealthComponent::TakeDamage applying damage of: %.2f"), Damage);
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

