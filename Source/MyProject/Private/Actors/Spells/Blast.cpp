// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spells/Blast.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABlast::ABlast()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(DefaultSceneComponent);

	ParticleEmitterComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Emitter Component"));
	ParticleEmitterComponent->SetupAttachment(DefaultSceneComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void ABlast::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlast::OnCollision);
	}
}

void ABlast::OnCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || OtherActor == GetOwner())
	{
		return;
	}

	if (OtherActor->IsA(ASpell::StaticClass()))
	{
		return;
	}
	
	DealDamage(OtherActor);
	if (HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
	}

	Destroy();
}

// Called every frame
void ABlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlast::Cast(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void ABlast::CastAtLocation(const FVector&)
{
}

