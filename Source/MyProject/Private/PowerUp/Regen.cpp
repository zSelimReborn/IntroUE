// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp/Regen.h"

#include "BaseCharacter.h"
#include "HealComponent.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARegen::ARegen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	RootComponent = DefaultSceneComponent;

	ParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle Component"));
	ParticleComponent->SetupAttachment(RootComponent);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TriggerCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerCapsule->SetupAttachment(RootComponent);

	HealComponent = CreateDefaultSubobject<UHealComponent>(TEXT("Heal Component"));
}

// Called when the game starts or when spawned
void ARegen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARegen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

