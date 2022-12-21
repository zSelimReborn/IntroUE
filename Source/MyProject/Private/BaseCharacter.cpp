// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseKey.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Interface/IInteractable.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh()); 
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	DisplayHudWidget();
	KeyInventory.Empty();
}

void ABaseCharacter::Interact()
{
	if (InteractableOverlappingActor)
	{
		InteractableOverlappingActor->Interact(this);
	}
}

void ABaseCharacter::DisplayHudWidget() const
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UUserWidget* HudWidget = CreateWidget(PlayerController, HudWidgetClass);
	if (HudWidget)
	{
		HudWidget->AddToViewport();
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::OnDeath(bool FellOutOfWorld)
{
	OnDeathPlayerEvent.Broadcast(FellOutOfWorld);
}

void ABaseCharacter::RegenHealth(const float& Health)
{
	HealthComponent->RestoreHealth(Health);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ABaseCharacter::Interact);
}

void ABaseCharacter::AddKeyToInventory(const FString& KeyName)
{
	KeyInventory.Add(KeyName);
	OnAddInventoryEvent.Broadcast(KeyName);
}

bool ABaseCharacter::HasKey(const FString& KeyName)
{
	return (KeyInventory.Find(KeyName) != INDEX_NONE);
}

float ABaseCharacter::GetCapsuleRadius() const
{
	return GetCapsuleComponent()->GetScaledCapsuleRadius();
}

float ABaseCharacter::GetCapsuleHalfHeight() const
{
	return GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

void ABaseCharacter::SetInteractableOverlappingActor(IIInteractable* Interactable)
{
	if (InteractableOverlappingActor)
	{
		InteractableOverlappingActor->HideInteractWidget();
	}

	InteractableOverlappingActor = Interactable;
}

void ABaseCharacter::ResetInteractableOverlappingActor(IIInteractable* Interactable)
{
	if (InteractableOverlappingActor == Interactable)
	{
		InteractableOverlappingActor = nullptr;
	}
}

float ABaseCharacter::GetMaxHealth() const
{
	return HealthComponent->GetMaxHealth();
}

float ABaseCharacter::GetCurrentHealth() const
{
	return HealthComponent->GetCurrentHealth();
}

float ABaseCharacter::GetCurrentHealthPercentage() const
{
	// CurrentHealth : MaxHealth = Percentage : 1
	const float MaxHealth = GetMaxHealth();
	const float CurrentHealth = GetCurrentHealth();

	const float Percentage = CurrentHealth/ MaxHealth;
	return Percentage;
}

float ABaseCharacter::GetMaxShield() const
{
	return HealthComponent->GetMaxShield();
}

float ABaseCharacter::GetCurrentShield() const
{
	return HealthComponent->GetCurrentShield();
}

float ABaseCharacter::GetCurrentShieldPercentage() const
{
	// CurrentShield : MaxShield = Percentage : 1
	const float MaxShield = GetMaxShield();
	const float CurrentShield = GetCurrentShield();

	const float Percentage = CurrentShield / MaxShield;
	return Percentage;
}

void ABaseCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath(true);
}
