// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"

#include "BaseCharacter.h"
#include "InteractableDoor.h"
#include "BaseKey.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ObjectiveWorldSubsystem.h"

constexpr float FLT_METERS(const float Meters) { return Meters * 100.f; }

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("MyProject.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle debugging for door interaction component."),
	ECVF_Default
);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OpenerTrigger = GetOwner()->FindComponentByClass<UBoxComponent>();
	Player = (GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())? GetWorld()->GetFirstPlayerController()->GetPawn() : nullptr;

	Door = Cast<AInteractableDoor>(GetOwner());
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformRotation(DeltaTime);
	DebugDraw();
}

bool UDoorInteractionComponent::CanOpenDoor() const
{
	// If no key configured, it's a door not locked
	if (KeyToOpen.IsEmpty()) { return true; }

	const TObjectPtr<ABaseCharacter> PlayerCasted = Cast<ABaseCharacter>(Player);
	if (PlayerCasted == nullptr) { return true; }

	return PlayerCasted->HasKey(KeyToOpen);
}

float UDoorInteractionComponent::GetAngleBetweenVectors(FVector A, FVector B)
{
	A.Normalize();
	B.Normalize();

	// Get the angle between two vectors
	const float CosineAngle = FVector::DotProduct(A, B);
	const float AngleRadians = FMath::Acos(CosineAngle);
	const float Angle = FMath::RadiansToDegrees(AngleRadians);

	return Angle;
}

bool UDoorInteractionComponent::IsPlayerLookingAtDoor(const APawn* Pawn)
{
	if (Pawn == nullptr || Door == nullptr)
	{
		return false;	
	}

	const FVector DoorCenter		= Door->GetMeshCenter();
	const FVector PlayerForward		= Pawn->GetActorForwardVector();
	const FVector DirectionToDoor	= DoorCenter - Pawn->GetActorLocation();
	
	const float Angle = GetAngleBetweenVectors(PlayerForward, DirectionToDoor);
	return (Angle <= PlayerFOVDegrees);
}

bool UDoorInteractionComponent::IsPlayerBehindDoor(const APawn* Pawn)
{
	if (Pawn == nullptr || Door == nullptr)
	{
		return false;	
	}

	const FVector DoorForward = GetOwner()->GetActorRightVector();
	const FVector DirectionToPlayer = Pawn->GetActorLocation() - Door->GetMeshCenter();

	const float Angle = GetAngleBetweenVectors(DoorForward, DirectionToPlayer);
	return (Angle > PlayerFOVDegrees);
}

void UDoorInteractionComponent::PerformRotation(const float DeltaTime)
{
	if (OpenerTrigger && Player)
	{
		// const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.f, 1.f);
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.f, 1.f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const float CurrentRotation = FMath::Lerp(0.f, DesiredYawRotation, RotationAlpha);

		switch (DoorState)
		{
		case EDoorState::Closed:
			if (Player && OpenerTrigger->IsOverlappingActor(Player) && IsPlayerLookingAtDoor(Player) && CanOpenDoor())
			{
				SetOpening();
				if (IsPlayerBehindDoor(Player))
				{
					DesiredYawRotation = FMath::Min(-DesiredYawRotation, DesiredYawRotation);
				}
				else
				{
					DesiredYawRotation = FMath::Abs(DesiredYawRotation);
				}
			}
			break;
		case EDoorState::Opened:
			if (!OpenerTrigger->IsOverlappingActor(Player))
			{
				SetClosing();
			}
			break;
		case EDoorState::Opening:
			if (CurrentRotationTime < TimeToRotate)
			{
				CurrentRotationTime += DeltaTime;
			}
			else
			{
				SetOpened();
				OpenedEvent.Broadcast();
			}
			break;
		case EDoorState::Closing:
			if (CurrentRotationTime > 0.f)
			{
				CurrentRotationTime = FMath::Max(0.f, CurrentRotationTime - DeltaTime);
			}
			else
			{
				SetClosed();
				ClosedEvent.Broadcast();
			}
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Door in an invalid state."));
			break;
		}

		if (Door)
		{
			Door->RotateDoor(CurrentRotation);
		}
	}
}

void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* Variable)
{
	UE_LOG(LogTemp, Display, TEXT("Change: %d"), Variable->GetBool());
}

void UDoorInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		const FVector Offset{FLT_METERS(0.75f), 0.f, FLT_METERS(2.5f)};
		const FString StateAsString = TEXT("DoorState: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();

		DrawDebugString(GetWorld(),Offset, StateAsString, GetOwner(), FColor::Red, 0.f);
	}
}

