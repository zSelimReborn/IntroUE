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
	TArray<TObjectPtr<ABaseKey>> KeyInventory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddKeyToInventory(const TObjectPtr<ABaseKey>);
	virtual bool HasKey(const TObjectPtr<ABaseKey>);

private:
	UPROPERTY(EditAnywhere, Category=Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category=Camera)
	UCameraComponent* FollowCamera;
};
