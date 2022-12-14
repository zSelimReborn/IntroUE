// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	DECLARE_EVENT_OneParam(FCheckpoint, FEnterCheckpoint, ACheckpoint*);
	DECLARE_EVENT_OneParam(FCheckpoint, FLeaveCheckpoint, ACheckpoint*);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE TObjectPtr<UBoxComponent> GetCheckpointArea() const { return CheckpointArea; };
	FORCEINLINE FVector GetRespawnLocation() const { return RespawnPoint->GetComponentLocation(); }
	FORCEINLINE FTransform GetRespawnTransform() const { return RespawnPoint->GetComponentTransform(); }

	FEnterCheckpoint& OnEnterCheckpoint() { return EnterCheckpointEvent; }
	FLeaveCheckpoint& OnLeaveCheckpoint() { return LeaveCheckpointEvent; }

protected:
	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<UBoxComponent> CheckpointArea;

	UPROPERTY(VisibleAnywhere, NoClear)
	TObjectPtr<USceneComponent> RespawnPoint;

	FEnterCheckpoint EnterCheckpointEvent;
	FLeaveCheckpoint LeaveCheckpointEvent;
};
