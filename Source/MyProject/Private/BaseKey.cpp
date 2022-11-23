// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseKey.h"

#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseKey::ABaseKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	SetRootComponent(MainMeshComponent);
	
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	ColliderComponent->SetupAttachment(MainMeshComponent);

	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseKey::OnColliderOverlap);
}

// Called when the game starts or when spawned
void ABaseKey::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseKey::OnColliderOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* PlayerCasted = Cast<ABaseCharacter>(OtherActor);
	// It's ABaseCharacter
	if (PlayerCasted != nullptr)
	{
		PlayerCasted->AddKeyToInventory(GetNameSafe(this));
		Destroy();
	}
}

// Called every frame
void ABaseKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

