// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseKey.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Components//ManaComponent.h"
#include "Interface/IInteractable.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Spell.h"
#include "Actors/Camera/CameraHighlight.h"
#include "Kismet/KismetMathLibrary.h"

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

	SpellSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spell Spawn Location"));
	SpellSpawnLocation->SetupAttachment(GetMesh());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	ManaComponent = CreateDefaultSubobject<UManaComponent>(TEXT("ManaComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	DisplayHudWidget();
	CreateCameraHighlightWidget();
	KeyInventory.Empty();
}

void ABaseCharacter::Interact()
{
	if (InteractableOverlappingActor)
	{
		InteractableOverlappingActor->Interact(this);
	}
}

void ABaseCharacter::OnStartInteract()
{
	OnPlayerInteractStart.Broadcast();
}

void ABaseCharacter::OnEndInteract()
{
	OnPlayerInteractEnd.Broadcast();
}

void ABaseCharacter::EnableLookAtCameraHighlight()
{
	bShouldUseCameraHighlight = true;
}

void ABaseCharacter::DisableLookAtCameraHighlight()
{
	bShouldUseCameraHighlight = false;
}

void ABaseCharacter::CheckAndLookAtHighlightObject()
{
	if (CurrentCameraHighlight && bShouldUseCameraHighlight)
	{
		LookAtObject(CurrentCameraHighlight->GetTargetActor());
	}
	else
	{
		RestoreDefaultView();	
	}
}

void ABaseCharacter::ChangeSpellSlot1()
{
	ChangeSpell(0);
}

void ABaseCharacter::ChangeSpellSlot2()
{
	ChangeSpell(1);
}

void ABaseCharacter::ChangeSpellSlot3()
{
	ChangeSpell(2);
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

void ABaseCharacter::CreateCameraHighlightWidget()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CameraHighlightWidget = CreateWidget(PlayerController, CameraHighlightWidgetClass);
}

void ABaseCharacter::DisplayCameraHighlightWidget() const
{
	if (CameraHighlightWidget && !CameraHighlightWidget->IsInViewport())
	{
		CameraHighlightWidget->AddToViewport();
	}
}

void ABaseCharacter::HideCameraHighlightWidget() const
{
	if (CameraHighlightWidget && CameraHighlightWidget->IsInViewport())
	{
		CameraHighlightWidget->RemoveFromViewport();
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckAndLookAtHighlightObject();
}

void ABaseCharacter::OnDeath(bool FellOutOfWorld)
{
	OnDeathPlayerEvent.Broadcast(FellOutOfWorld);
}

void ABaseCharacter::RegenHealth(const float& Health)
{
	HealthComponent->RestoreHealth(Health);
}

void ABaseCharacter::Cast()
{
	if (!ManaComponent->HasMana())
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector CastSpawnLocation; FRotator CastSpawnRotation;
	GetCastSpawnPoint(CastSpawnLocation, CastSpawnRotation);

	const TSubclassOf<ASpell> CurrentSpell = SpellInventory.IsValidIndex(CurrentSpellIndex)? SpellInventory[CurrentSpellIndex] : nullptr;

	if (CurrentSpell)
	{
		ASpell* NewSpell = GetWorld()->SpawnActor<ASpell>(
			CurrentSpell,
			CastSpawnLocation,
			CastSpawnRotation,
			SpawnParams
		);

		if (NewSpell)
		{
			NewSpell->Cast(CastSpawnRotation.Vector());
			ManaComponent->UseMana(NewSpell->GetManaCost());
		}
	}
}

void ABaseCharacter::ChangeSpell(const int8 Index)
{
	if (SpellInventory.IsValidIndex(Index))
	{
		CurrentSpellIndex = Index;
	} else
	{
		CurrentSpellIndex = 0;
	}
}

void ABaseCharacter::GetCastSpawnPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraLocation = SpellSpawnLocation->GetComponentLocation();
	
	FVector CameraOffset;
	CameraOffset.Set(0.0f, 0.0f, 0.0f);
	OutLocation = CameraLocation + FTransform(CameraRotation).TransformVector(CameraOffset);
	
	// Skew the aim to be slightly upwards.
	OutRotation = CameraRotation;
	OutRotation.Pitch += 10.0f;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ABaseCharacter::OnStartInteract);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &ABaseCharacter::OnEndInteract);
	
	PlayerInputComponent->BindAction("Cast", EInputEvent::IE_Pressed, this, &ABaseCharacter::Cast);
	PlayerInputComponent->BindAction("Highlight", EInputEvent::IE_Pressed, this, &ABaseCharacter::EnableLookAtCameraHighlight);
	PlayerInputComponent->BindAction("Highlight", EInputEvent::IE_Released, this, &ABaseCharacter::DisableLookAtCameraHighlight);

	PlayerInputComponent->BindAction("SpellSlot1", EInputEvent::IE_Pressed, this, &ABaseCharacter::ChangeSpellSlot1);
	PlayerInputComponent->BindAction("SpellSlot2", EInputEvent::IE_Pressed, this, &ABaseCharacter::ChangeSpellSlot2);
	PlayerInputComponent->BindAction("SpellSlot3", EInputEvent::IE_Pressed, this, &ABaseCharacter::ChangeSpellSlot3);
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

void ABaseCharacter::AddCameraAttractor(AAttractors* CameraAttractor)
{
	CurrentAttractors.Add(CameraAttractor);
}

void ABaseCharacter::RemoveCameraAttractor(AAttractors* CameraAttractor)
{
	CurrentAttractors.Remove(CameraAttractor);
}

bool ABaseCharacter::HasCameraAttractor() const
{
	return CurrentAttractors.Num() > 0;
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

float ABaseCharacter::GetMaxMana() const
{
	return ManaComponent->GetMaxMana();
}

float ABaseCharacter::GetCurrentMana() const
{
	return ManaComponent->GetCurrentMana();
}

float ABaseCharacter::GetCurrentManaPercentage() const
{
	// CurrentMana : MaxMana = Percentage : 1
	const float MaxMana = GetMaxMana();
	const float CurrentMana = GetCurrentMana();

	const float Percentage = CurrentMana / MaxMana;
	return Percentage;
}

void ABaseCharacter::LookAtObject(const AActor* OtherActor)
{
	if (CameraBoom && OtherActor)
	{
		const FVector DirectionToActor = OtherActor->GetActorLocation() - GetActorLocation();
		const FRotator RotationToActor = DirectionToActor.Rotation();

		CameraBoom->bInheritYaw = false;
		CameraBoom->bUsePawnControlRotation = false;
		const FLatentActionInfo ActionInfo{INDEX_NONE, INDEX_NONE, nullptr, this};

		float OverTime = 0.f;
		if (CurrentCameraHighlight)
		{
			OverTime = CurrentCameraHighlight->GetTimeToMoveCamera();
		}
		
		UKismetSystemLibrary::MoveComponentTo(CameraBoom, FVector{0.f, 0.f, 0.f}, RotationToActor, true,
		true, OverTime, false, EMoveComponentAction::Move, ActionInfo);
	}
}

void ABaseCharacter::RestoreDefaultView() const
{
	if (CameraBoom)
	{
		CameraBoom->SetRelativeRotation(FRotator::ZeroRotator);
		CameraBoom->bUsePawnControlRotation = true;
		CameraBoom->bInheritYaw = true;
	}
}

void ABaseCharacter::SetCameraHighlight(ACameraHighlight* CameraHighlight)
{
	CurrentCameraHighlight = CameraHighlight;
	DisplayCameraHighlightWidget();
}

void ABaseCharacter::RemoveCameraHighlight()
{
	CurrentCameraHighlight = nullptr;
	RestoreDefaultView();
	HideCameraHighlightWidget();
}

void ABaseCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	OnDeath(true);
}
