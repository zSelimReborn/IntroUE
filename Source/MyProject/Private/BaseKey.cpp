// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseKey.h"

#include "BaseCharacter.h"
#include "Components/PickupItemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseKey::ABaseKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	SetRootComponent(MainMeshComponent);
	
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ColliderComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	ColliderComponent->SetupAttachment(MainMeshComponent);

	PickupWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Pickup Widget Component"));
	PickupWidgetComponent->SetupAttachment(MainMeshComponent);

	PickupItemComponent = CreateDefaultSubobject<UPickupItemComponent>(TEXT("Pickup Item Component"));
}

// Called when the game starts or when spawned
void ABaseKey::BeginPlay()
{
	Super::BeginPlay();

	HidePickupWidget();
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseKey::OnColliderOverlapStart);
	ColliderComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseKey::OnColliderOverlapEnd);
	PickupItemComponent->OnInteractionSuccess.AddDynamic(this, &ABaseKey::AfterPickupKey);
}

void ABaseKey::HidePickupWidget()
{
	if (PickupWidgetComponent)
	{
		PickupWidgetComponent->SetVisibility(false);
	}
}

void ABaseKey::ShowPickupWidget()
{
	if (PickupWidgetComponent)
	{
		PickupWidgetComponent->SetVisibility(true);
	}
}

void ABaseKey::OnColliderOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABaseCharacter>(OtherActor) != nullptr)
	{
		ShowPickupWidget();
	}
}

void ABaseKey::OnColliderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HidePickupWidget();
}

void ABaseKey::AfterPickupKey()
{
	OnPickupKey.Broadcast();
}

// Called every frame
void ABaseKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

