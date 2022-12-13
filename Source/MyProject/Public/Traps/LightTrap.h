// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightTrap.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;
class UPersistentDamageComponent;

UCLASS()
class MYPROJECT_API ALightTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ToggleTrap();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UNiagaraComponent> ParticleSystemComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UCapsuleComponent> TriggerCapsule;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UPersistentDamageComponent> DealDamageComponent;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float ToggleTime = 5.f;

	UPROPERTY(NoClear)
	FTimerHandle ToggleTimer;
};
