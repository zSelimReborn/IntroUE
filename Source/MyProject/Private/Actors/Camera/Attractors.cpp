// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Camera/Attractors.h"

#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAttractors::AAttractors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(DefaultSceneComponent);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerVolume->SetupAttachment(DefaultSceneComponent);
}

// Called when the game starts or when spawned
void AAttractors::BeginPlay()
{
	Super::BeginPlay();

	PrepareTriggerVolume();
}

ABaseCharacter* AAttractors::GetPlayer() const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	return Cast<ABaseCharacter>(PlayerPawn);
}

void AAttractors::AddAttractorToPlayer()
{
	ABaseCharacter* Player = GetPlayer();
	if (Player)
	{
		Player->AddCameraAttractor(this);
	}
}

void AAttractors::RemoveAttractorFromPlayer()
{
	ABaseCharacter* Player = GetPlayer();
	if (Player)
	{
		Player->RemoveCameraAttractor(this);
	}
}

void AAttractors::PrepareTriggerVolume()
{
	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AAttractors::OnOverlapStart);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AAttractors::OnOverlapEnd);
	}
}

void AAttractors::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController && CameraComponent)
	{
		AddAttractorToPlayer();
		PlayerController->SetViewTargetWithBlend(this, BlendTime);
	}
}

void AAttractors::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	RemoveAttractorFromPlayer();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseCharacter* Player = GetPlayer();
	if (PlayerController && Player)
	{
		if (!Player->HasCameraAttractor())
		{
			PlayerController->SetViewTargetWithBlend(Player, BlendTime);
		}
	}
}

// Called every frame
void AAttractors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

