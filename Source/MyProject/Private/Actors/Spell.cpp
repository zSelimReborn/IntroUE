// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spell.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpell::DealDamage(AActor* Actor)
{
	UGameplayStatics::ApplyDamage(
		Actor,
		Damage,
		nullptr,
		nullptr,
		DamageType
	);
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpell::Cast(const FVector&)
{
}

void ASpell::CastAtLocation(const FVector& Location)
{
}

