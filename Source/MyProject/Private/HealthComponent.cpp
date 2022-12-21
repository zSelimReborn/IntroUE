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
	CurrentShield = MaxShield;
	// CurrentShieldRegenerationTime must start from the current shield amount (in percentage).
	CurrentShieldRegenerationTime = ShieldRegenerationTime;
	
	Player = Cast<ABaseCharacter>(GetOwner());
	SetupOnDamageDelegate();
}

void UHealthComponent::OnDeath()
{
	ResetShieldCooldownTimer();
	// If player handle death to respawn
	if (Player)
	{
		Player->OnDeath(false);
	}
	else
	{
		GetOwner()->Destroy();
	}
}

void UHealthComponent::SetupOnDamageDelegate()
{
	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	}
}

void UHealthComponent::StartShieldCooldownTimer()
{
	GetOwner()->GetWorldTimerManager().SetTimer(ShieldCooldownTimer, this, &UHealthComponent::OnEndShieldCooldown, ShieldCooldown, false);
}

void UHealthComponent::ResetShieldCooldownTimer()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(ShieldCooldownTimer);
}

void UHealthComponent::OnEndShieldCooldown()
{
	SetShieldState(EShieldState::Regenerating);
}

void UHealthComponent::UpdateCurrentShieldRegenerationTime()
{
	// CurrentShieldRegenerationTime : ShieldRegenerationTime = CurrentShield : MaxShield
	CurrentShieldRegenerationTime = (ShieldRegenerationTime * CurrentShield) / MaxShield;
}

void UHealthComponent::RegenShield(const float& DeltaTime)
{
	float RegenAlpha = 0.f;
	float CurrentRegeneration = 0.f;
	
	switch (GetShieldState()) {
		case EShieldState::Regenerating:
			CurrentShieldRegenerationTime += DeltaTime;

			RegenAlpha = FMath::Clamp(CurrentShieldRegenerationTime / ShieldRegenerationTime, 0.f, 1.f);
			CurrentRegeneration = FMath::Lerp(0.f, MaxShield, RegenAlpha);
		
			if (CurrentShieldRegenerationTime > ShieldRegenerationTime)
			{
				SetShieldState(EShieldState::Complete);
			}

			CurrentShield = CurrentRegeneration;
			break;
		case EShieldState::Complete:
		case EShieldState::Cooldown:
		default: ;
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

		const FVector ShieldOffset{0.f, 0.f, -5.f};
		const FString ShieldAsString = TEXT("Shield: ") + FString::SanitizeFloat(CurrentShield);
		
		DrawDebugString(GetWorld(), HealthOffset, HealthAsString, GetOwner(), FColor::Red, 0.f);
		DrawDebugString(GetWorld(), ShieldOffset, ShieldAsString, GetOwner(), FColor::Blue, 0.f);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RegenShield(DeltaTime);
	DebugDraw();
}

void UHealthComponent::TakeDamage(const float& Damage)
{
	if (Damage <= 0.f || IsDead())
	{
		return;
	}

	float RemainingDamage = Damage;
	if (HasShield())
	{
		// If the shield is < Damage means there's still damage to absorb. It will be dealt to health
		RemainingDamage = (CurrentShield <= Damage)? FMath::Abs(CurrentShield - Damage) : 0.f;
		CurrentShield = FMath::Clamp(CurrentShield - Damage, 0.f, MaxShield);
		UpdateCurrentShieldRegenerationTime();
		ResetShieldCooldownTimer();
		StartShieldCooldownTimer();
		SetShieldState(EShieldState::Cooldown);
	}
	
	CurrentHealth = FMath::Clamp(CurrentHealth - RemainingDamage, 0.f, MaxHealth);
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

