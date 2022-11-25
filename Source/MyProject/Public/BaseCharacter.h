// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABaseKey;

UCLASS()
class MYPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);

	UPROPERTY(Transient, VisibleAnywhere)
	TArray<FString> KeyInventory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddKeyToInventory(const FString&);
	virtual bool HasKey(const FString&);

	float GetCapsuleRadius() const;
	float GetCapsuleHalfHeight() const;

	DECLARE_EVENT_OneParam(FBaseCharacter, FOnAddInventory, const FString&);
	FOnAddInventory& OnAddInventory() { return OnAddInventoryEvent; }

private:
	UPROPERTY(EditAnywhere, Category=Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category=Camera)
	UCameraComponent* FollowCamera;

	FOnAddInventory OnAddInventoryEvent;
};
