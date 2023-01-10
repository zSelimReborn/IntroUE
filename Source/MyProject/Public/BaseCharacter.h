// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABaseKey;
class IIInteractable;
class UUserWidget;
class AAttractors;
class ACameraHighlight;

DECLARE_MULTICAST_DELEGATE(FPlayerInteractStart);
DECLARE_MULTICAST_DELEGATE(FPlayerInteractEnd);

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
	void Interact();
	void OnStartInteract();
	void OnEndInteract();
	void EnableLookAtCameraHighlight();
	void DisableLookAtCameraHighlight();
	void ChangeSpellSlot1();
	void ChangeSpellSlot2();
	void ChangeSpellSlot3();

	void DisplayHudWidget() const;

	void CreateCameraHighlightWidget();
	void DisplayCameraHighlightWidget() const;
	void HideCameraHighlightWidget() const;
	void CheckAndLookAtHighlightObject();

	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	UPROPERTY(Transient, VisibleAnywhere)
	TArray<FString> KeyInventory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnDeath(bool);
	virtual void RegenHealth(const float&);

	virtual void Cast();
	void ChangeSpell(const int8 Index);
	void GetCastSpawnPoint(FVector&, FRotator&) const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddKeyToInventory(const FString&);
	virtual bool HasKey(const FString&);

	float GetCapsuleRadius() const;
	float GetCapsuleHalfHeight() const;

	DECLARE_EVENT_OneParam(FBaseCharacter, FOnAddInventory, const FString&);
	FOnAddInventory& OnAddInventory() { return OnAddInventoryEvent; }

	DECLARE_EVENT_OneParam(FBaseCharacter, FOnDeathPlayer, bool);
	FOnDeathPlayer& OnDeathPlayer() { return OnDeathPlayerEvent; }

	FPlayerInteractStart OnPlayerInteractStart;
	FPlayerInteractEnd OnPlayerInteractEnd;

	void SetInteractableOverlappingActor(IIInteractable* Actor);
	void ResetInteractableOverlappingActor(IIInteractable* Actor);

	void AddCameraAttractor(AAttractors*);
	void RemoveCameraAttractor(AAttractors*);
	bool HasCameraAttractor() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthPercentage() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxShield() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentShield() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentShieldPercentage() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentManaPercentage() const;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	void LookAtObject(const AActor*);
	void RestoreDefaultView() const;
	void SetCameraHighlight(ACameraHighlight*);
	void RemoveCameraHighlight();
	
private:
	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, NoClear, Category=Health)
	TObjectPtr<class UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, NoClear, Category=Mana)
	TObjectPtr<class UManaComponent> ManaComponent;

	UPROPERTY(VisibleAnywhere, NoClear, Category=Spell)
	TObjectPtr<USceneComponent> SpellSpawnLocation;

	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<UUserWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere, Category=Spell)
	TArray<TSubclassOf<class ASpell>> SpellInventory;

	UPROPERTY(VisibleAnywhere, Category=Spell)
	int8 CurrentSpellIndex = 0;

	FOnAddInventory OnAddInventoryEvent;
	FOnDeathPlayer OnDeathPlayerEvent;

	TObjectPtr<IIInteractable> InteractableOverlappingActor;

	UPROPERTY(VisibleAnywhere, Transient)
	TArray<AAttractors*> CurrentAttractors;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<ACameraHighlight> CurrentCameraHighlight;

	UPROPERTY(VisibleAnywhere, Transient)
	bool bShouldUseCameraHighlight = false;

	UPROPERTY(EditAnywhere, Category="Camera Highlight")
	TSubclassOf<UUserWidget> CameraHighlightWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> CameraHighlightWidget;
};
