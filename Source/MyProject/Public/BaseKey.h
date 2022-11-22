// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKey.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class MYPROJECT_API ABaseKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnColliderOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MainMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> ColliderComponent = nullptr;

	UPROPERTY(EditAnywhere)
	FString KeyName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FString GetKeyName() const { return KeyName; }
};
