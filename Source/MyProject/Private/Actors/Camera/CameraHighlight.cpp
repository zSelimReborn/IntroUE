// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Camera/CameraHighlight.h"

#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraHighlight::ACameraHighlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetupAttachment(DefaultSceneComponent);
}

// Called when the game starts or when spawned
void ACameraHighlight::BeginPlay()
{
	Super::BeginPlay();

	PrepareTriggerVolume();
}

ABaseCharacter* ACameraHighlight::GetPlayer() const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	return Cast<ABaseCharacter>(PlayerPawn);
}

void ACameraHighlight::PrepareTriggerVolume()
{
	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACameraHighlight::OnOverlapStart);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ACameraHighlight::OnOverlapEnd);
	}
}

void ACameraHighlight::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Set Camera Highlight on Player

	ABaseCharacter* Player = GetPlayer();
	if (Player)
	{
		Player->SetCameraHighlight(this);
	}
}

void ACameraHighlight::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Remove Camera Highlight from Player
	ABaseCharacter* Player = GetPlayer();
	if (Player)
	{
		Player->RemoveCameraHighlight();
	}
}

// Called every frame
void ACameraHighlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

