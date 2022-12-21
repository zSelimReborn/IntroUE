// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UENUM()
enum class EShieldState
{
	Complete		UMETA(DisplayName="Complete"),
	Regenerating	UMETA(DisplayName="Regenerating"),
	Cooldown		UMETA(DisplayName="Cooldown")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnDeath();

	void SetupOnDamageDelegate();

	void StartShieldCooldownTimer();
	void ResetShieldCooldownTimer();
	void OnEndShieldCooldown();
	void UpdateCurrentShieldRegenerationTime();
	void RegenShield(const float&);
	FORCEINLINE void SetShieldState(const EShieldState& State) { ShieldState = State; }

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	void DebugDraw() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(const float&);
	void RestoreHealth(const float&);
	
	FORCEINLINE bool IsDead() const { return CurrentHealth <= 0.f; }
	FORCEINLINE bool HasShield() const { return CurrentShield > 0.f; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetMaxShield() const { return MaxShield; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetCurrentShield() const { return CurrentShield; }

	FORCEINLINE EShieldState GetShieldState() const { return ShieldState; }
	
protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category="Health|Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Transient, Category="Health|Health")
	float CurrentHealth = 0.f;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category="Health|Shield")
	float MaxShield = 100.f;

	UPROPERTY(VisibleAnywhere, Transient, Category="Health|Shield")
	float CurrentShield = 0.f;

	UPROPERTY(EditAnywhere, Category="Health|Shield")
	float ShieldRegenerationTime = 1.f;

	UPROPERTY(EditAnywhere, Category="Health|Shield")
	float ShieldCooldown = 2.5f;

	UPROPERTY(VisibleAnywhere, Transient, Category="Health|Shield")
	float CurrentShieldRegenerationTime = 0.f;

	UPROPERTY(VisibleAnywhere, Transient, Category="Health|Shield")
	EShieldState ShieldState = EShieldState::Complete;
	
	FTimerHandle ShieldCooldownTimer;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<class ABaseCharacter> Player; 
};
