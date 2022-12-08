// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PrepareTrigger();

	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float HealQty = 0.f;

	UPROPERTY(EditAnywhere)
	bool bDestroyOnHeal = false;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<class UShapeComponent> TriggerShape;
};
