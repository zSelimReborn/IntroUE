// Fill out your copyright notice in the Description page of Project Settings.


#include "WallInteractionComponent.h"

#include "InteractableWall.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UWallInteractionComponent::UWallInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Trigger = GetOwner()->FindComponentByClass<UBoxComponent>();
	Player = (GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())? GetWorld()->GetFirstPlayerController()->GetPawn() : nullptr;

	Wall = Cast<AInteractableWall>(GetOwner());
}


// Called every frame
void UWallInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformMove(DeltaTime);
}

void UWallInteractionComponent::PerformMove(const float DeltaTime)
{
	// Once opened, no further actions must be done
	if (IsOpened())
	{
		return;
	}
	
	if (Trigger && Player)
	{
		const float TimeRatio = FMath::Clamp(CurrentOpeningTime / TimeToMove, 0.f, 1.f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const float CurrentOpening = FMath::Lerp(0.f, DesiredZOffset, RotationAlpha);
		
		switch (WallState)
		{
		case EWallState::Closed:
			if (Player && Trigger->IsOverlappingActor(Player))
			{
				SetOpening();
				ClosePressurePlate();
			}
			break;
		case EWallState::Opening:
			if (CurrentOpeningTime < TimeToMove)
			{
				CurrentOpeningTime += DeltaTime;
			}
			else
			{
				SetOpened();
			}
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Wall in an invalid state."));
			break;
		}

		if (Wall)
		{
			Wall->MoveWall(CurrentOpening);
		}
	}

}

void UWallInteractionComponent::ClosePressurePlate() const
{
	if (Wall)
	{
		Wall->MovePressurePlate(0.f);
	}
}

