// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "Components/BoxComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(DefaultSceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(DefaultSceneComponent);

	CheckpointArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Checkpoint Area"));
	CheckpointArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CheckpointArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CheckpointArea->SetupAttachment(DefaultSceneComponent);

	RespawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Respawn Point Location"));
	RespawnPoint->SetupAttachment(DefaultSceneComponent);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	CheckpointArea->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapStart);
	CheckpointArea->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
}

void ACheckpoint::OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		EnterCheckpointEvent.Broadcast(this);
	}
}

void ACheckpoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor != this)
	{
		LeaveCheckpointEvent.Broadcast(this);
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

