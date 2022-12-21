// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spell.h"
#include "Blast.generated.h"

UCLASS()
class MYPROJECT_API ABlast : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Cast(const FVector&) override;
	virtual void CastAtLocation(const FVector&) override;

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<class UParticleSystemComponent> ParticleEmitterComponent;
};
