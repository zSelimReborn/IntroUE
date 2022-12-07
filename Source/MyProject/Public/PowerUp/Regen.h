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

	virtual void PrepareTrigger();

	UFUNCTION()
	virtual void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float RegenHealth = 0.f;
	
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UNiagaraComponent> ParticleComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UCapsuleComponent> TriggerCapsule;
};
