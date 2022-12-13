// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbstractDealDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAbstractDealDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbstractDealDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void PrepareTrigger();

	FORCEINLINE void ResetOverlappingActor() { OverlappingActor = nullptr; }
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ApplyDamage(const float&);
	
	FORCEINLINE bool ShouldDealDamage() const { return bShouldDealDamage; }
	virtual void SetShouldDealDamage(const bool);
	
protected:
	UPROPERTY(Transient, VisibleAnywhere, NoClear, Category=Damage)
	TObjectPtr<UShapeComponent> TriggerComponent;

	UPROPERTY(VisibleAnywhere, Transient, Category=Damage)
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY(VisibleAnywhere, Category=Damage)
	bool bShouldDealDamage = true;
};
