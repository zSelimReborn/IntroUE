// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attractors.generated.h"

class ABaseCharacter;

UCLASS()
class MYPROJECT_API AAttractors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttractors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ABaseCharacter* GetPlayer() const;
	void AddAttractorToPlayer();
	void RemoveAttractorFromPlayer();
	void PrepareTriggerVolume();

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere, NoClear, Category="Camera Attractors")
	TObjectPtr<class UBoxComponent> TriggerVolume;

	UPROPERTY(VisibleAnywhere, NoClear, Category="Camera Attractors")
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category="Camera Attractors")
	float BlendTime = 0.2f;
};
