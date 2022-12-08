// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Regen.generated.h"

UCLASS()
class MYPROJECT_API ARegen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARegen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UNiagaraComponent> ParticleComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UCapsuleComponent> TriggerCapsule;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UHealComponent> HealComponent;
};
