// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartRestoreManaTimer();
	void OnEndRestoreManaTimer();
	void RestoreMana(const float&);

	// Debug tools
	void DebugDraw() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetMaxMana() const { return MaxMana; }
	FORCEINLINE float GetCurrentMana() const { return CurrentMana; }

	void UseMana(const float&);
	void FillMana(const float&);

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category=Mana)
	float MaxMana = 100.f;

	UPROPERTY(VisibleAnywhere, Category=Mana)
	float CurrentMana = 0.f;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category=Mana)
	float RestoreManaPerSeconds = 5.f;

	UPROPERTY(EditAnywhere, Category=Mana)
	float RestoreSeconds = 15.f;

	FTimerHandle RestoreManaTimer;
};
