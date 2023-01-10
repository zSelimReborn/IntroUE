// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKey.generated.h"

class UStaticMeshComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickupKey);

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

	void HidePickupWidget();
	void ShowPickupWidget();

	UFUNCTION()
	void OnColliderOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnColliderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void AfterPickupKey();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MainMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> ColliderComponent = nullptr;

	UPROPERTY(VisibleAnywhere, NoClear, Category="Pickup Item")
	TObjectPtr<class UWidgetComponent> PickupWidgetComponent;

	UPROPERTY(VisibleAnywhere, NoClear, Category="Pickup Item")
	TObjectPtr<class UPickupItemComponent> PickupItemComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FPickupKey OnPickupKey;
};
