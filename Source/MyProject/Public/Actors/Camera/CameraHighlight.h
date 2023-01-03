// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Actor.h"
#include "CameraHighlight.generated.h"

UCLASS()
class MYPROJECT_API ACameraHighlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraHighlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ABaseCharacter* GetPlayer() const;
	void PrepareTriggerVolume();

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }
	FORCEINLINE float GetTimeToMoveCamera() const { return TimeToMoveCamera; }

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;
	
	UPROPERTY(VisibleAnywhere, NoClear, Category="Camera Highlight")
	TObjectPtr<class UBoxComponent> TriggerVolume;

	UPROPERTY(EditAnywhere, Category="Camera Highlight")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, Category="Camera Highlight")
	float TimeToMoveCamera = 0.4f;
};
