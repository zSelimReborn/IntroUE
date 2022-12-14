// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/LightTrap.h"

#include "DealDamageComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "PersistentDamageComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALightTrap::ALightTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	RootComponent = DefaultSceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);

	ParticleSystemComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Particle Component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerCapsule->SetupAttachment(RootComponent);

	DealDamageComponent = CreateDefaultSubobject<UPersistentDamageComponent>(TEXT("Damage Dealer"));
}

// Called when the game starts or when spawned
void ALightTrap::BeginPlay()
{
	Super::BeginPlay();

	ParticleSystemComponent->SetVisibility(DealDamageComponent->ShouldDealDamage());
	// GetOwner()->GetWorldTimerManager().SetTimer(DealerTimer, this, &UPersistentDamageComponent::RestartDamage, Seconds, false);
	GetWorldTimerManager().SetTimer(ToggleTimer, this, &ALightTrap::ToggleTrap, ToggleTime, true);
}

void ALightTrap::ToggleTrap()
{
	ParticleSystemComponent->ToggleVisibility();
	DealDamageComponent->SetShouldDealDamage(!DealDamageComponent->ShouldDealDamage());
}

// Called every frame
void ALightTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

