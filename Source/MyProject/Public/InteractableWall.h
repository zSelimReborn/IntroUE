// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableWall.generated.h"

class UBoxComponent;
class UWallInteractionComponent;

UCLASS()
class MYPROJECT_API AInteractableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveWall(float ZOffset) const;
	void MovePressurePlate(float ZOffset) const;

protected:
	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<USceneComponent> MainComponent;
	
	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> WallMeshComponent;

	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> TriggerMeshComponent;

	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UBoxComponent> TriggerBoxComponent;

	UPROPERTY(EditAnywhere, NoClear)
	TObjectPtr<UWallInteractionComponent> WallInteractionComponent;
};
