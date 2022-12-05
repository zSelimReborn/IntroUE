// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


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

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(const float&);
	void RestoreHealth(const float&);
	
	FORCEINLINE bool IsDead() const { return CurrentHealth <= 0.f; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	
protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Transient)
	float CurrentHealth = 0.f;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<class ABaseCharacter> Player; 
};
