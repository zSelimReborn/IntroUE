// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PersistentDamageComponent.generated.h"

UENUM()
enum class EDealerDamageState
{
	DealingDmg		UMETA(DisplayName="Dealing Damage"),
	CoolDown		UMETA(DisplayName="Cooling Down"),
	Default			UMETA(DisplayName="Default"),
	MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPersistentDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPersistentDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PrepareTrigger();

	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FORCEINLINE void SetDealingDamage() { CurrentState = EDealerDamageState::DealingDmg; }
	FORCEINLINE void SetCoolDown() { CurrentState = EDealerDamageState::CoolDown; }
	FORCEINLINE void SetDefaultState() { CurrentState = EDealerDamageState::Default; }
	FORCEINLINE void ResetOverlappingActor() { OverlappingActor = nullptr; }

	void RestartDamage();
	void StartTimer();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage() const;

	FORCEINLINE EDealerDamageState GetState() const { return CurrentState; }
	FORCEINLINE bool IsDealingDamage() const { return CurrentState == EDealerDamageState::DealingDmg; }
	FORCEINLINE bool IsCoolingDown() const { return CurrentState == EDealerDamageState::CoolDown; }

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float DamagePerSeconds = 0.f;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float Seconds = 1.f;

	UPROPERTY(VisibleAnywhere)
	EDealerDamageState CurrentState = EDealerDamageState::Default;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<class UShapeComponent> TriggerShape;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY(NoClear)
	FTimerHandle DealerTimer;
};
